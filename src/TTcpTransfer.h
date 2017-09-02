#ifndef _TTCPTRANSFER_H_
#define _TTCPTRANSFER_H_

#include "file_operator.h"
#include <QTcpServer>
#include <QTcpSocket>

class TTcpTransfer
{
public:
	TTcpTransfer(File_Operator  *mFileOperater, qint64 totalSize);
	~TTcpTransfer();
public:
	bool  Start();
	bool  Prepare();
	bool  WaitForConnect(int seconds);
	bool  WaitForFinished(int seconds);
	bool  TransferData();

	int   GetTcpPort(){ return mnTcpPort; }
	QString GetServeUrl(){ return mstrResultUrl; }

protected:

private:
	QTcpServer       *mpTCPServer;
	QTcpSocket       *mpTCPSocket;
	File_Operator    *mpFileOperator;
	bool			 mbSuccess;
	QString			 mstrResultUrl;
	int				 mnTcpPort;
	qint64			 mqTotalSize;
};


#endif //_TTCPTRANSFER_H_