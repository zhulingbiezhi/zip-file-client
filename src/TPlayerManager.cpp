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
	qDebug() << __FUNCTION__ << QTime::currentTime();
	if (pFileOperator == NULL)
	{
		return false;
	}
	if (/*mmapPlayRecord.contains(mstrUuid)*/0)
	{
		mpWebView->LoadPage(mmapPlayRecord.value(mstrUuid));
		return true;
	}
	
	QString  strUrl;
	if (Play(pFileOperator, strUrl))
	{
		mmapPlayRecord.insert(mstrUuid, strUrl);
		return true; 
	}
	else
	{
		return false;
	}
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

bool TPlayerManager::Play(File_Operator * pFileOperator, QString& strUrl)
{
	qDebug() << __FUNCTION__ << "111" << QTime::currentTime();
	if (nullptr != mpZipServer)
	{
		delete mpZipServer;
		mpZipServer = nullptr;
	}
	mpZipServer = new TZipServer();
	strUrl = mpZipServer->StartServer(pFileOperator, mqSize);	
	//strUrl = "http://127.0.0.1:8088/index.html";
	qDebug() << __FUNCTION__ << "222" << QTime::currentTime();

	if (!strUrl.isEmpty())
	{
		mbPause = false;
		mpWebView->LoadPage(strUrl);
		mpWebViewRender->AddWidget(mpWebView->GetWebView());
		return true;
	}
	return false;
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
	//mpHttpServer->CloseAllServer();
}
