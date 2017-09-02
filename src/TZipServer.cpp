#include "TZipServer.h"
#include <QApplication>

TZipServer::TZipServer()
: mpProcess(nullptr)
, mpTcpTransfer(nullptr)
{
	
}

TZipServer::~TZipServer()
{
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

QString TZipServer::StartServer(File_Operator * pFileOperator, qint64 qSize)
{
	if (nullptr == mpTcpTransfer)
	{
		mpTcpTransfer = new TTcpTransfer(pFileOperator, qSize);
	}	
	if (mpTcpTransfer->Prepare())
	{			
		mpProcess = new QProcess;
		QStringList argList;
		argList << "h5server" << QString("%1").arg(mpTcpTransfer->GetTcpPort()) << QString("%1").arg(qSize);
		qDebug() << argList.join(" ");
		mpProcess->start(QApplication::applicationDirPath() + "/hfserver.exe", argList);
		bool bRet = mpTcpTransfer->Start();
		if (bRet)
		{
			return mpTcpTransfer->GetServeUrl();
		}
	}
	return "";
}
