#ifndef _TWEBENGINEVIEW_H_
#define _TWEBENGINEVIEW_H_
#include <QWebEngineView>

#include <QEvent>

/*class TWebView;*/
#include "TWebView.h"
class TWebEnginePage;

class TWebEngineView : public TWebView
{
	Q_OBJECT
public:
	TWebEngineView(QWidget * parent);
	~TWebEngineView();

	virtual void LoadPage(const QString& url);

	virtual void Reload();

	virtual void Stop();

	virtual QWidget* GetWebView();

	virtual bool eventFilter(QObject *, QEvent *);

public slots:
	void onFeaturePermissionRequested(const QUrl & securityOrigin, QWebEnginePage::Feature feature);
	void OnContextMenuRequested(const QPoint &pos);
	

private:
	QWebEngineView			*mpWebEngineView;
	TWebEnginePage			*mpWebEnginePage;
};



#endif