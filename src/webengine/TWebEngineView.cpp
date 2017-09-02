#include "TWebView.h"
#include "TWebEngineView.h"
#include "TWebEnginePage.h"
#include <QWebEngineSettings>

TWebEngineView::TWebEngineView(QWidget * parent)
: TWebView()
{
	mpWebEngineView = new QWebEngineView(parent);
	mpWebEngineView->installEventFilter(this);
	mpWebEnginePage = new TWebEnginePage(mpWebEngineView);
	mpWebEngineView->setContextMenuPolicy(Qt::CustomContextMenu);

	mpWebEngineView->setPage(mpWebEnginePage);
	mpWebEnginePage->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
	//mpWebEnginePage->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	mpWebEnginePage->settings()->setDefaultTextEncoding("utf-8");
	mpWebEngineView->show();

	QObject::connect(mpWebEngineView, &QWidget::customContextMenuRequested, this, &TWebEngineView::OnContextMenuRequested);
	QObject::connect(mpWebEngineView, &QWebEngineView::loadFinished, this, &TWebView::onLoadFinished);
	QObject::connect(mpWebEnginePage, &QWebEnginePage::featurePermissionRequested, this, &TWebEngineView::onFeaturePermissionRequested);
}

TWebEngineView::~TWebEngineView()
{
	qDebug() << __FUNCTION__;
}

void TWebEngineView::LoadPage(const QString& url)
{
	mstrPlayingUrl = url;
	//mstrPlayingUrl = "D:\\test_movie\\test.html";
	mpWebEnginePage->load(QUrl(mstrPlayingUrl));
}

void TWebEngineView::Reload()
{
	mpWebEnginePage->load(QUrl(mstrPlayingUrl));
}

void TWebEngineView::Stop()
{
	mpWebEnginePage->load(QUrl(""));
}

QWidget* TWebEngineView::GetWebView()
{
	return mpWebEngineView;
}

void TWebEngineView::onFeaturePermissionRequested(const QUrl & securityOrigin, QWebEnginePage::Feature feature)
{
	qDebug() << __FUNCTION__ << securityOrigin.toString() << feature;
}

bool TWebEngineView::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == qobject_cast<QObject*>(mpWebEngineView))
	{
		qDebug() << e->type();
		if (e->type() == QEvent::ContextMenu)
		{
			e->ignore();
			return false;
		}
		return mpWebEngineView->eventFilter(obj, e);
	}
}

void TWebEngineView::OnContextMenuRequested(const QPoint &pos)
{
	qDebug() << __FUNCTION__ << pos;

}
