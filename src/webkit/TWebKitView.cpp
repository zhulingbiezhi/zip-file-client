#include "TWebKitView.h"
//#include "TWebPage.h"
#include "TWebMediaPlugin.h"
#include "TContextMenu.h"

#include <QWebFrame>
#include <QEvent>
#include <QWebHistory>

TWebKitView::TWebKitView(QWidget * parent)
: TWebView()
{
	mpWebKitView = new QWebView(parent);
	//mpWebKitView->page() = new TWebPage(mpWebKitView);
	mpContextMenu = new TContextMenu(mpWebKitView);
	mpContextMenu->setVisible(false);
	mpWebKitView->setPage(mpWebKitView->page());
	mpWebKitView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	mpWebKitView->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	mpWebKitView->page()->settings()->setMaximumPagesInCache(10);
	mpWebKitView->page()->settings()->setDefaultTextEncoding("utf-8");
	//mpWebKitView->customContextMenuRequested()
	mpWebKitView->show();
	mpWebKitView->installEventFilter(this);
	connect(mpWebKitView, &QWebView::loadFinished, this, &TWebKitView::OnLoadFinished);
	connect(mpContextMenu, &TContextMenu::sigBack, this, &TWebKitView::OnActionBack);
	connect(mpContextMenu, &TContextMenu::sigForward, this, &TWebKitView::OnActionForward);
	connect(mpContextMenu, &TContextMenu::sigReload, this, &TWebKitView::OnActionReload);
}

TWebKitView::~TWebKitView()
{

}

void TWebKitView::LoadPage(const QString& url)
{
	mpContextMenu->setVisible(false);
	mstrPlayingUrl = url;
	mbFirstLoad = true;
	//mstrPlayingUrl = "file:///D://test_movie//test.html";	
	mpWebKitView->page()->mainFrame()->load(QUrl(mstrPlayingUrl));		
	mpWebKitView->history()->clear();
}

void TWebKitView::Reload()
{
	mpContextMenu->setVisible(false);
	mpWebKitView->page()->mainFrame()->load(QUrl(mstrPlayingUrl));
}

void TWebKitView::Stop()
{
	mpContextMenu->setVisible(false);
	mpWebKitView->page()->mainFrame()->load(QUrl(""));
}

QWidget* TWebKitView::GetWebView()
{
	return mpWebKitView;
}

bool TWebKitView::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == mpWebKitView)
	{
// 		if (e->type() != QEvent::Paint && e->type() != QEvent::Timer  && e->type() != QEvent::MouseMove  && e->type() != QEvent::ToolTipChange  && e->type() != QEvent::UpdateLater)
// 		qDebug() << __FUNCTION__ <<"mpWebKitView  " <<  e->type();
		if (e->type() == QEvent::ContextMenu)
		{
			QPoint curPos = QCursor::pos();
// 			QRect webGeometry = mpWebKitView->geometry();
// 			QPoint tarnsferPos = mpWebKitView->mapFromGlobal(curPos);
// 			QRect contextGeometry = mpContextMenu->geometry();
			mpContextMenu->setGeometry(curPos.x(), curPos.y(), 160, 90);
			mpContextMenu->setVisible(true);
			e->ignore();
			return true;
		}
		else if (e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::Hide)
		{
			mpContextMenu->setVisible(false);
		}
		
	}
	return __super::eventFilter(obj, e);
}

void TWebKitView::OnActionBack(bool)
{
	mpContextMenu->setVisible(false);
	mpWebKitView->back();
}

void TWebKitView::OnActionForward(bool)
{
	mpContextMenu->setVisible(false);
	mpWebKitView->forward();
	
}

void TWebKitView::OnActionReload(bool)
{
	mpContextMenu->setVisible(false);	
	mpWebKitView->reload();
}

void TWebKitView::OnLoadFinished()
{
	if (mbFirstLoad)
	{
		mbFirstLoad = false;
		mpWebKitView->history()->clear();
	}
	mpContextMenu->SetBackForwardState(mpWebKitView->history()->canGoBack(), mpWebKitView->history()->canGoForward());
}
