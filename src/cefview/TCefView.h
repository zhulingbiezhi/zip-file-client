#ifndef _TCEFVIEWH_
#define _TCEFVIEWH_

#include "TWebView.h"
#include "TCefHandle.h"

class TCefView : public TWebView
{
	Q_OBJECT
public:
	TCefView(QWidget * parent);
	~TCefView();

	virtual void LoadPage(const QString& url);
	virtual void Reload();
	virtual void Stop();
	virtual QWidget* GetWebView();

	virtual void LoadBlank();

private:
	TCefHandle      *mpCefHandle;
	QWidget         *mpParent;
};

#endif //_TCefHandle_H_