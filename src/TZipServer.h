#ifndef _TZIPSERVER_H_
#define _TZIPSERVER_H_

#include "TTcpTransfer.h"

#include <QProcess>
#include <QThread>

class TZipServer :public QObject
{
	Q_OBJECT
public:
	TZipServer();
	~TZipServer();

	void StartServer(File_Operator * pFileOperator, qint64 qSize);
protected:

	private slots :
		void onPrepareFinished(const int& port);

signals:
	void sigParseFinished(const QString& url);

private:
	TTcpTransfer				*mpTcpTransfer;
	QProcess					*mpProcess;
	QThread 					*mpTcpThread;
	qint64						 mqZipSize;
};


#endif //_TZIPSERVER_H_