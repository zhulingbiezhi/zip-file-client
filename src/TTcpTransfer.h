#ifndef _TTCPTRANSFER_H_
#define _TTCPTRANSFER_H_

#include "file_operator.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class TTcpTransfer : public QObject
{
	Q_OBJECT
public:
	TTcpTransfer(File_Operator  *mFileOperater, qint64 totalSize);
	~TTcpTransfer();

public:
	Q_INVOKABLE bool  Start();
	Q_INVOKABLE bool  Prepare();
	void Stop();

private:
	bool  WaitForConnect(int seconds);
	bool  WaitForFinished(int seconds);
	bool  TransferData();
	void  TransferNeedData();

protected:


signals :
	void sigPrepareFinished(const int& port);
	void sigParseFinished(const QString& url);

private:
	QTcpServer       *mpTCPServer;
	QTcpSocket       *mpTCPSocket;
	File_Operator    *mpFileOperator;
	bool			 mbSuccess;
	//QString			 mstrResultUrl;
	//int				 mnTcpPort;
	qint64			 mqTotalSize;
	bool			 mbStop;
};


#endif //_TTCPTRANSFER_H_