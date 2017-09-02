#include "TTcpTransfer.h"

TTcpTransfer::TTcpTransfer(File_Operator  *pFileOperator, qint64 totalSize)
: mbSuccess(true)
, mpTCPSocket(nullptr)
, mnTcpPort(8080)
, mpFileOperator(pFileOperator)
, mqTotalSize(totalSize)
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
		mstrResultUrl = "http://127.0.0.1" + resultUrl + "/index.html";
		qDebug() << __FUNCTION__ << mstrResultUrl;
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
	mnTcpPort = mpTCPServer->serverPort();
}

bool TTcpTransfer::Start()
{
	WaitForConnect(1);
	TransferData();
	WaitForFinished(10);
	return mbSuccess;
}
