#ifndef _TNETWORKACCESSMANAGER_H_
#define _TNETWORKACCESSMANAGER_H_

class QNetworkAccessManager;

class TNetworkAccessManager : public QNetworkAccessManager
{
public:
	TNetworkAccessManager(QObject *parent = 0);

	virtual ~TNetworkAccessManager();

protected:
	virtual QNetworkReply * createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);

};

#endif
