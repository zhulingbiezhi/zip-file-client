#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QNetworkAccessManager>

#include "TNetworkAccessManager.h"

TNetworkAccessManager::TNetworkAccessManager(QObject *parent)
: QNetworkAccessManager(parent)
{

}


TNetworkAccessManager::~TNetworkAccessManager()
{

}

QNetworkReply * TNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData /*= 0*/)
{
	//qDebug() << __FUNCTION__ << request.url().toString();
	return __super::createRequest(op, request, outgoingData);
}
