#ifndef _TWEBENGINEPAGE_H_
#define _TWEBENGINEPAGE_H_

#include <QWebEnginePage>
#include <QAuthenticator>

class TWebEnginePage : public QWebEnginePage
{
	Q_OBJECT
public:
	TWebEnginePage(QObject * parent);
	~TWebEnginePage();

	virtual void triggerAction(WebAction action, bool checked = false);

	virtual QWebEnginePage * createWindow(WebWindowType type);

	virtual QStringList chooseFiles(FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes);

	virtual void javaScriptAlert(const QUrl &securityOrigin, const QString& msg);

	virtual bool javaScriptConfirm(const QUrl &securityOrigin, const QString& msg);

	virtual bool javaScriptPrompt(const QUrl &securityOrigin, const QString& msg, const QString& defaultValue, QString* result);

	virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID);

	virtual bool certificateError(const QWebEngineCertificateError &certificateError);

	virtual bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);

public slots:
	void linkHovered(const QString &url);
	void selectionChanged();
	void geometryChangeRequested(const QRect& geom);
	void windowCloseRequested();

	void featurePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
	void featurePermissionRequestCanceled(const QUrl &securityOrigin, QWebEnginePage::Feature feature);

	void authenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator);
	void proxyAuthenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator, const QString &proxyHost);
};


#endif