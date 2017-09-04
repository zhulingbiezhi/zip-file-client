#include "TPlayerManager.h"
#include "TWebView.h"
#include "TWebViewRender.h"
#include "TZipServer.h"

#ifdef USE_WEBKIT
#include "TWebKitView.h"
#endif
#ifdef USE_WEBENGINE
#include "TWebEngineView.h"
#endif
#ifdef USE_CEF
#include "TCefView.h"
#endif

#include <QTime>

TPlayerManager::TPlayerManager()
: mpZipServer(nullptr)
, mbPause(false)
{
	mpWebViewRender = new TWebViewRender();
#ifdef USE_WEBKIT
	mpWebView = new TWebKitView(mpWebViewRender);
#elif defined USE_WEBENGINE
	mpWebView = new TWebEngineView(mpWebViewRender);
#else
	mpWebView = new TCefView(mpWebViewRender);
#endif
	mpWebViewRender->AddWidget(mpWebView->GetWebView());
	mmapPlayRecord.clear();
}


TPlayerManager::~TPlayerManager()
{
	// 	if (mpWebView)
	// 	{
	// 		//delete mpWebView;
	// 		mpWebView->deleteLater();
	// 	}
	// 	if (mpWebViewRender)
	// 	{
	// 		//delete mpWebViewRender;
	// 		mpWebViewRender->deleteLater();
	// 	}
	if (mpZipServer)
	{
		delete mpZipServer;
	}
}

QWidget * TPlayerManager::getPlayerWidget()
{
	return mpWebViewRender;
}

bool TPlayerManager::setSymmetricKey(PlayItem::SymEncryptionType type, const QByteArray &key, const QByteArray &iv)
{
	return false;
}

bool TPlayerManager::playFileOperator(File_Operator * pFileOperator, qint64 pos /*= 0*/)
{
	mpFileOperator = pFileOperator;
	if (pFileOperator == NULL)
	{
		return false;
	}
	if (/*mmapPlayRecord.contains(mstrUuid)*/0)
	{
		mpWebView->LoadPage(mmapPlayRecord.value(mstrUuid));
		return true;
	}
	qDebug() << __FUNCTION__ << "111" << QTime::currentTime();
	if (nullptr != mpZipServer)
	{
		disconnect(mpZipServer, &TZipServer::sigParseFinished, this, &TPlayerManager::onParseFinished);
		delete mpZipServer;
		mpZipServer = nullptr;
	}
	qDebug() << __FUNCTION__ << "222" << QTime::currentTime();
	mpZipServer = new TZipServer();
	connect(mpZipServer, &TZipServer::sigParseFinished, this, &TPlayerManager::onParseFinished);
	mpZipServer->StartServer(pFileOperator, mqSize);
}

void TPlayerManager::setPlayInfo(const QString &name, const QVariant &param, const QVariant &, const QVariant &, const QVariant &)
{
	if (name == "size")
	{
		mqSize = param.toLongLong();
	}
	else if (name == "uuid")
	{
		mstrUuid = param.toString();
	}
}

bool TPlayerManager::pause(bool bPause)
{
	if (bPause)
	{
		mbPause = true;
		mpWebView->LoadBlank();
	}
	else
	{
		if (mbPause)
		{
			mbPause = false;
			mpWebView->Reload();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void TPlayerManager::SetMprxHotAreaInfo(const QMap<int, CubicShapeMap> & shapeMap, const QImage & data, QString externInfo)
{
	qDebug() << __FUNCTION__ << externInfo;

}

void TPlayerManager::clear()
{
	qDebug() << __FUNCTION__;
	if (nullptr != mpZipServer)
	{
		delete mpZipServer;
		mpZipServer = nullptr;
	}
}

void TPlayerManager::onParseFinished(const QString& url)
{
	//strUrl = "http://127.0.0.1:8088/index.html";
	qDebug() << __FUNCTION__ << "333" << QTime::currentTime();
	if (!url.isEmpty())
	{
		QString strUrl = url + "/index.html";
		qDebug() << __FUNCTION__ << strUrl;
		mpWebView->LoadPage(strUrl);
		mpWebViewRender->AddWidget(mpWebView->GetWebView());
	}
	else
	{
		qDebug() << __FUNCTION__ << "the url is empty !";
	}
}
