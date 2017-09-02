#include "TWebPage.h"
#include <QWebPage>
#include <QDebug>
#include <QWebFrame>
#include <QNetworkRequest>
#include <QEvent>

TWebPage::TWebPage(QObject *parent) : QWebPage(parent)
{
	connect(this, &QWebPage::frameCreated, this, &TWebPage::onFrameCreated);
	connect(this, &QWebPage::contentsChanged, this, &TWebPage::onContentsChanged);
	connect(this, &QWebPage::downloadRequested, this, &TWebPage::onDownloadRequested);
	connect(this, &QWebPage::featurePermissionRequested, this, &TWebPage::onFeaturePermissionRequested);
	connect(this, &QWebPage::linkClicked, this, &TWebPage::onLinkClicked);
	connect(this, &QWebPage::linkHovered, this, &TWebPage::onLinkHovered);
	connect(this, &QWebPage::loadStarted, this, &TWebPage::onLoadStarted);
	connect(this, &QWebPage::printRequested, this, &TWebPage::onPrintRequested);
	connect(this, &QWebPage::unsupportedContent, this, &TWebPage::onUnsupportedContent);
	connect(this, &QWebPage::loadProgress, this, &TWebPage::onLoadProgress);
	connect(this, &QWebPage::loadFinished, this, &TWebPage::onLoadFinished);
}


TWebPage::~TWebPage()
{
}

QWebPage * TWebPage::createWindow(WebWindowType type)
{
	//Q_UNUSED(type);
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return this;
}

bool TWebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{
	//qDebug() << __FUNCTION__ << request.url().toString();
	//throw std::logic_error("The method or operation is not implemented.");
	return QWebPage::acceptNavigationRequest(frame, request, type);
}

QString TWebPage::userAgentForUrl(const QUrl& url) const
{
	//qDebug() << __FUNCTION__ << url.toString();
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::userAgentForUrl(url);
}

QString TWebPage::chooseFile(QWebFrame *originatingFrame, const QString& oldFile)
{
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::chooseFile(originatingFrame, oldFile);
}

void TWebPage::javaScriptAlert(QWebFrame *originatingFrame, const QString& msg)
{
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::javaScriptAlert(originatingFrame, msg);
}

bool TWebPage::javaScriptConfirm(QWebFrame *originatingFrame, const QString& msg)
{
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::javaScriptConfirm(originatingFrame, msg);
}

bool TWebPage::javaScriptPrompt(QWebFrame *originatingFrame, const QString& msg, const QString& defaultValue, QString* result)
{
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::javaScriptPrompt(originatingFrame, msg, defaultValue, result);
}

void TWebPage::javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID)
{
	//qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
	return __super::javaScriptConsoleMessage(message, lineNumber, sourceID);
}

void TWebPage::onFrameCreated(QWebFrame * frame)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onContentsChanged()
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onDownloadRequested(const QNetworkRequest & request)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onFeaturePermissionRequested(QWebFrame * frame, QWebPage::Feature feature)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onLinkClicked(const QUrl & url)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onLinkHovered(const QString & link, const QString & title, const QString & textContent)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onLoadStarted()
{
	qDebug() << __FUNCTION__;
}

void TWebPage::onPrintRequested(QWebFrame * frame)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onUnsupportedContent(QNetworkReply * reply)
{
	//qDebug() << __FUNCTION__;
}

void TWebPage::onLoadProgress(int progress)
{
	qDebug() << __FUNCTION__ << progress;
}

void TWebPage::onLoadFinished(bool ok)
{
	qDebug() << __FUNCTION__;
}

bool TWebPage::eventFilter(QObject *obj, QEvent *e)
{
	return __super::eventFilter(obj, e);
}

void TWebPage::customEvent(QEvent *e)
{
	qDebug() << __FUNCTION__ << e->type();
	//throw std::logic_error("The method or operation is not implemented.");
}
