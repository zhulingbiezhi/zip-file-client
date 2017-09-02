#ifndef _TWEBVIEW_H_
#define _TWEBVIEW_H_

#include <QWidget>
#include <QVBoxLayout>

class TWebView : public QObject
{
	Q_OBJECT
public:
	TWebView();
	virtual ~TWebView();

public:
	virtual void LoadBlank() = 0;
	virtual void LoadPage(const QString& url) = 0;
	virtual void Reload() = 0;
	virtual void Stop() = 0;
	virtual QWidget* GetWebView() = 0;

protected:
	QString       mstrPlayingUrl;
};

#endif