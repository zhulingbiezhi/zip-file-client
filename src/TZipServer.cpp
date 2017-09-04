#include "TZipServer.h"
#include <QApplication>

TZipServer::TZipServer()
: mpProcess(nullptr)
, mpTcpTransfer(nullptr)
{
	mpTcpThread = new QThread();
}

TZipServer::~TZipServer()
{
	mpTcpTransfer->Stop();
	if (mpTcpThread)
	{
		if (mpTcpThread->isRunning())
		{
			mpTcpThread->quit();
			mpTcpThread->wait();
		}
		delete mpTcpThread;
	}
	if (mpTcpTransfer)
	{
		delete mpTcpTransfer;
	}
	if (mpProcess)
	{
		mpProcess->kill();
		delete mpProcess;
	}
}

void TZipServer::StartServer(File_Operator * pFileOperator, qint64 qSize)
{
	mpTcpTransfer = new TTcpTransfer(pFileOperator, qSize);
	mpTcpTransfer->moveToThread(mpTcpThread);
	connect(mpTcpTransfer, &TTcpTransfer::sigPrepareFinished, this, &TZipServer::onPrepareFinished);
	connect(mpTcpTransfer, &TTcpTransfer::sigParseFinished, this, &TZipServer::sigParseFinished);
	mpTcpThread->start();
	mqZipSize = qSize;
	QMetaObject::invokeMethod(mpTcpTransfer, "Prepare");
}

void TZipServer::onPrepareFinished(const int& port)
{
	mpProcess = new QProcess;
	QStringList argList;
	argList << "h5server" << QString("%1").arg(port) << QString("%1").arg(mqZipSize);
	qDebug() << argList.join(" ");
	QMetaObject::invokeMethod(mpTcpTransfer, "Start");
	mpProcess->start(QApplication::applicationDirPath() + "/hfserver.exe", argList);
}