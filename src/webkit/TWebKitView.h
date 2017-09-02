#ifndef _TWEBKITVIEW_H_
#define _TWEBKITVIEW_H_

#include <QWebView>

#include "TWebView.h"

//class TWebPage;
class TContextMenu;

class TWebKitView : public TWebView
{
	Q_OBJECT
public:
	TWebKitView(QWidget * parent);
	virtual ~TWebKitView();

	virtual void LoadPage(const QString& url);

	virtual void Reload();

	virtual void Stop();

	virtual QWidget* GetWebView();

	virtual bool eventFilter(QObject *, QEvent *);

private slots:
	void OnActionBack(bool);
	void OnActionForward(bool);
	void OnActionReload(bool);
	void OnLoadFinished();

private:
	QWebView			*mpWebKitView;
	//TWebPage			*mpWebKitPage;
	TContextMenu        *mpContextMenu;
	bool				mbFirstLoad;
};


#endif