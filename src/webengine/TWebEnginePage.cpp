#include "TWebEnginePage.h"

TWebEnginePage::TWebEnginePage(QObject * parent)
: QWebEnginePage(parent)
{
	connect(this, &QWebEnginePage::linkHovered, this, &TWebEnginePage::linkHovered);
	connect(this, &QWebEnginePage::selectionChanged, this, &TWebEnginePage::selectionChanged);
	connect(this, &QWebEnginePage::geometryChangeRequested, this, &TWebEnginePage::geometryChangeRequested);
	connect(this, &QWebEnginePage::windowCloseRequested, this, &TWebEnginePage::windowCloseRequested);
	connect(this, &QWebEnginePage::featurePermissionRequested, this, &TWebEnginePage::featurePermissionRequested);
	connect(this, &QWebEnginePage::featurePermissionRequestCanceled, this, &TWebEnginePage::featurePermissionRequestCanceled);
	connect(this, &QWebEnginePage::authenticationRequired, this, &TWebEnginePage::authenticationRequired);
	connect(this, &QWebEnginePage::proxyAuthenticationRequired, this, &TWebEnginePage::proxyAuthenticationRequired);
}


TWebEnginePage::~TWebEnginePage()
{
}

void TWebEnginePage::triggerAction(WebAction action, bool checked /*= false*/)
{
	qDebug() << __FUNCTION__;
	return __super::triggerAction(action, checked);
}

QWebEnginePage * TWebEnginePage::createWindow(WebWindowType type)
{
	qDebug() << __FUNCTION__ << type;
	return __super::createWindow(type);
}

QStringList TWebEnginePage::chooseFiles(FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes)
{
	qDebug() << __FUNCTION__ << mode << oldFiles << acceptedMimeTypes;
	return __super::chooseFiles(mode, oldFiles, acceptedMimeTypes);
}

void TWebEnginePage::javaScriptAlert(const QUrl &securityOrigin, const QString& msg)
{
	qDebug() << __FUNCTION__ << securityOrigin.toString() << msg;
	return __super::javaScriptAlert(securityOrigin, msg);
}

bool TWebEnginePage::javaScriptConfirm(const QUrl &securityOrigin, const QString& msg)
{
	qDebug() << __FUNCTION__ << securityOrigin.toString() << msg;
	return __super::javaScriptConfirm(securityOrigin, msg);
}

bool TWebEnginePage::javaScriptPrompt(const QUrl &securityOrigin, const QString& msg, const QString& defaultValue, QString* result)
{
	qDebug() << __FUNCTION__ << securityOrigin.toString() <<  msg << defaultValue << result;
	return __super::javaScriptPrompt(securityOrigin, msg, defaultValue, result);
}

void TWebEnginePage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID)
{
	qDebug() << __FUNCTION__ << level << message << lineNumber << sourceID;
	return __super::javaScriptConsoleMessage(level, message, lineNumber, sourceID);
}

bool TWebEnginePage::certificateError(const QWebEngineCertificateError &certificateError)
{
	qDebug() << __FUNCTION__ << certificateError.error() << certificateError.url().toString() << certificateError.errorDescription();
	return __super::certificateError(certificateError);
}

bool TWebEnginePage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
	qDebug() << __FUNCTION__ << url.toString() << type << isMainFrame;
	return __super::acceptNavigationRequest(url, type, isMainFrame);
}

void TWebEnginePage::linkHovered(const QString &url)
{
	qDebug() << __FUNCTION__ << url;
}

void TWebEnginePage::selectionChanged()
{
	qDebug() << __FUNCTION__ ;
}

void TWebEnginePage::geometryChangeRequested(const QRect& geom)
{
	qDebug() << __FUNCTION__ << geom.width() << geom.height();
}

void TWebEnginePage::windowCloseRequested()
{
	qDebug() << __FUNCTION__ ;
}

void TWebEnginePage::featurePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
	qDebug() << __FUNCTION__ << securityOrigin.toString() << feature;
}

void TWebEnginePage::featurePermissionRequestCanceled(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
	qDebug() << __FUNCTION__;
}

void TWebEnginePage::authenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator)
{
	qDebug() << __FUNCTION__ << requestUrl.toString() << authenticator->user() << authenticator->password();
}
 
void TWebEnginePage::proxyAuthenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator, const QString &proxyHost)
{
	qDebug() << __FUNCTION__ << requestUrl.toString() << authenticator->user() << authenticator->password() << proxyHost;
}
