#ifndef _TCEFHANDLE_H_
#define _TCEFHANDLE_H_

#include <QCefView.h>

enum EContextMenu
{
	ECM_Back,
	ECM_Forward,
	ECM_Reload
};

class TCefHandle : public QCefView
{
	Q_OBJECT
public:
	TCefHandle(const QString& url, QWidget* parent = 0);
	~TCefHandle();

private:
	virtual void processQCefUrlRequest(const QString& url) override;

	virtual void processQCefQueryRequest(const QCefQuery& query) override;

	virtual void onLoadStateChange(bool isLoading) override;

	virtual void onLoadStart() override;

	virtual void onLoadEnd(int httpStatusCode) override;

	virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl) override;

//	virtual void onInvokeMethodNotify(const QString& method, const QVariantList& arguments) override;

	virtual void onUrlChange(const QString& url) override;

	virtual bool excContextMenu(int id) override;

	virtual bool getMenuInfo(int index, int& command, QString& lblName, bool& itemEnable) override;

	virtual bool eventFilter(QObject *obj, QEvent *e) override;

	virtual void onKeyEvent(const int& key) override;

protected:
	
private:

public slots:

signals:

private:

};

#endif //_TCEFHANDLE_H_