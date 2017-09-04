#include "TTcpTransfer.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>

TTcpTransfer::TTcpTransfer(File_Operator  *pFileOperator, qint64 totalSize)
: mbSuccess(true)
, mpTCPSocket(nullptr)
, mpFileOperator(pFileOperator)
, mqTotalSize(totalSize)
, mbStop(false)
{

}

TTcpTransfer::~TTcpTransfer()
{
	if (nullptr != mpTCPServer)
	{
		mpTCPServer->close();
		delete mpTCPServer;
	}
}

bool TTcpTransfer::WaitForConnect(int seconds)
{
	if (!mbSuccess) {
		return false;
	}

	if (!mpTCPServer->waitForNewConnection(seconds * 1000))
	{
		qDebug() << "wait connection timeout";
		mbSuccess = false;
		return false;
	}
	else
	{
		mpTCPSocket = mpTCPServer->nextPendingConnection();
		return true;
	}
}

bool TTcpTransfer::WaitForFinished(int seconds)
{
	if (!mbSuccess) {
		return false;
	}
	if (!mpTCPSocket->waitForReadyRead(seconds * 1000))
	{
		qDebug() << "wait reply timeout";
		return false;
	}
	else
	{
		QByteArray resultUrl = mpTCPSocket->readAll();
		if (resultUrl.isEmpty())
		{
			qDebug() << "reply is empty";
			return false;
		}


		//mstrResultUrl = "http://127.0.0.1" + resultUrl + "/index.html";
		//		qDebug() << __FUNCTION__ << mstrResultUrl;
		return true;
	}
}

bool TTcpTransfer::TransferData()
{
	if (!mbSuccess) {
		return false;
	}

	File_Handle hFile = mpFileOperator->fopen(mpFileOperator);
	char* pDataBuff = new char[1024 * 1024];
	QByteArray tempData;
	qint64 qSentSize = 0;

	while (true)
	{
		int nReadCount = mpFileOperator->fread(pDataBuff, 1, 1024 * 1024, hFile);
		if (nReadCount == 0) {
			qDebug() << __FUNCTION__ << "nReadCount == 0";
			if (qSentSize == mqTotalSize){
				qDebug() << __FUNCTION__ << "send data finished ";
				break;
			}
		}
		tempData.append(pDataBuff, nReadCount);
		if (qSentSize + nReadCount > mqTotalSize)
		{
			qDebug() << "tcp change size" << mqTotalSize << nReadCount << qSentSize;
			nReadCount = mqTotalSize - qSentSize;
			tempData = tempData.mid(0, nReadCount);
		}
		qint64 writeSize = mpTCPSocket->write(tempData);
		tempData.clear();
		if (writeSize != nReadCount || !mpTCPSocket->waitForBytesWritten(1000))
		{
			qDebug() << "tcp write fail" << writeSize << nReadCount << qSentSize;
			mbSuccess = false;
			break;
		}
		qSentSize += writeSize;
	}
	mpFileOperator->fclose(hFile);
	if (nullptr != pDataBuff)
	{
		delete pDataBuff;
	}
	return mbSuccess;
}

bool TTcpTransfer::Prepare()
{
	mpTCPServer = new QTcpServer;						//建立TCP服务，用于传输数据给hfserver.exe
	mpTCPServer->setMaxPendingConnections(1);
	if (!mpTCPServer->listen(QHostAddress("127.0.0.1")))
	{
		mbSuccess = false;
		return false;
	}
	emit sigPrepareFinished(mpTCPServer->serverPort());
}

bool TTcpTransfer::Start()
{
	WaitForConnect(1);
#if 0
	TransferData();
	WaitForFinished(10);
#else
	TransferNeedData();
#endif

	return mbSuccess;
}

void TTcpTransfer::TransferNeedData()
{
	if (!mbSuccess) {
		return;
	}
	File_Handle hFile = mpFileOperator->fopen(mpFileOperator);
	char* pDataBuff = new char[1024 * 64];
	int  transferLen = 1024 * 64;
	QByteArray tempData;
	qint64 curStartFilePos, curEndFilePos;
	while (true)
	{
		if (mbStop) {
			break;
		}
		curStartFilePos = curEndFilePos = 0;
		QList<qint64>   areaList;
		if (mpTCPSocket->waitForReadyRead(100)/*mpTCPSocket->bytesAvailable() > 0*/)
		{
			QJsonParseError json_error;
			QByteArray recPos = mpTCPSocket->readAll();
			//qDebug() << __FUNCTION__ << QString(recPos);
			QByteArray jsonArray = recPos;
			QList<QByteArray>  jsonList;
			do
			{
				int jsonSpiltIndex = jsonArray.indexOf("}{");
				//qDebug() << jsonArray;
				if (jsonSpiltIndex != -1)
				{
					jsonList.append(jsonArray.mid(0, jsonSpiltIndex + 1));
					jsonArray = jsonArray.mid(jsonSpiltIndex + 1);
				}
				else
				{
					jsonList.append(jsonArray);
					break;
				}
			} while (true);
			if (jsonArray.contains("url"))
			{
				QString strUrl = jsonArray.mid(4);
				qDebug() << jsonArray << strUrl;
				emit sigParseFinished(strUrl);
				continue;
			}
			qDebug() << __FUNCTION__ << jsonList;
			for each(QByteArray jsonData in jsonList)
			{
				QJsonDocument parse_doucment = QJsonDocument::fromJson(jsonData, &json_error);
				if (json_error.error == QJsonParseError::NoError)
				{
					if (parse_doucment.isObject())
					{
						QJsonObject obj = parse_doucment.object();
						curStartFilePos = obj.value("startPos").toVariant().toLongLong();
						curEndFilePos = obj.value("endPos").toVariant().toLongLong();
						areaList.append(curStartFilePos);
						areaList.append(curEndFilePos);
					}
				}
			}
		}
		if (areaList.size() % 2 != 0 || areaList.isEmpty()) {
			continue;
		}
		for (int i = 0; i < areaList.size(); i += 2)
		{
			curStartFilePos = areaList.at(i);
			curEndFilePos = areaList.at(i + 1);
			if (curEndFilePos <= curStartFilePos)
			{
				continue;
			}
			int seekRet = mpFileOperator->fseek(hFile, curStartFilePos, 0);
			int nReadCount = mpFileOperator->fread(pDataBuff, 1, transferLen, hFile);
			if (nReadCount == 0) {
				qDebug() << __FUNCTION__ << "nReadCount == 0";
				break;
			}

			tempData.append(pDataBuff, nReadCount);
			QJsonObject sendJson;
			sendJson.insert("startPos", curStartFilePos);
			sendJson.insert("endPos", curStartFilePos + nReadCount - 1);
			sendJson.insert("size", nReadCount);
			sendJson.insert("data", QString(tempData.toBase64()));
			QJsonDocument sendDocument;
			sendDocument.setObject(sendJson);
			QByteArray byte_array = sendDocument.toJson(QJsonDocument::Compact);
			qint64 arraySize = byte_array.size();
			qint64 writeSize = mpTCPSocket->write(byte_array);
			qDebug() << curStartFilePos << nReadCount;
			if (arraySize != writeSize || !mpTCPSocket->waitForBytesWritten(1000))
			{
				qDebug() << "tcp write fail" << writeSize << nReadCount;
				mbSuccess = false;
				break;
			}
			tempData.clear();
		}
	}
	mpFileOperator->fclose(hFile);
	if (nullptr != pDataBuff)
	{
		delete pDataBuff;
	}
}

void TTcpTransfer::Stop()
{
	mbStop = true;
}
