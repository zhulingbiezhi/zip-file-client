#ifndef _TZIPSERVER_H_
#define _TZIPSERVER_H_

#include "TTcpTransfer.h"

#include <QProcess>

class TZipServer
{
public:
	TZipServer();
	~TZipServer();

	QString StartServer(File_Operator * pFileOperator, qint64 qSize);
protected:

private:
	TTcpTransfer				*mpTcpTransfer;
	QProcess					*mpProcess;
};


#endif //_TZIPSERVER_H_