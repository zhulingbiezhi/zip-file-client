#ifndef _TWEBPAGE_H_
#define _TWEBPAGE_H_

#include <QWebPage>
#include <QNetworkReply>

class TWebPage : public QWebPage
{
	Q_OBJECT
public:
	explicit TWebPage(QObject *parent = 0);
	~TWebPage();

protected:
	virtual QWebPage * createWindow(WebWindowType type);

	virtual bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

	virtual QString userAgentForUrl(const QUrl& url) const;

	virtual QString chooseFile(QWebFrame *originatingFrame, const QString& oldFile);

	virtual void javaScriptAlert(QWebFrame *originatingFrame, const QString& msg);

	virtual bool javaScriptConfirm(QWebFrame *originatingFrame, const QString& msg);

	virtual bool javaScriptPrompt(QWebFrame *originatingFrame, const QString& msg, const QString& defaultValue, QString* result);

	virtual void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);


	public slots:
	//void	onApplicationCacheQuotaExceeded(QWebSecurityOrigin * origin, quint64 defaultOriginQuota, quint64 totalSpaceNeeded);
	void	onContentsChanged();
	//void	onDatabaseQuotaExceeded(QWebFrame * frame, QString databaseName);
	void	onDownloadRequested(const QNetworkRequest & request);
	//void	onFeaturePermissionRequestCanceled(QWebFrame * frame, QWebPage::Feature feature);
	void	onFeaturePermissionRequested(QWebFrame * frame, QWebPage::Feature feature);
	void	onFrameCreated(QWebFrame * frame);
	//void	onGeometryChangeRequested(const QRect & geom);
	void	onLinkClicked(const QUrl & url);
	void	onLinkHovered(const QString & link, const QString & title, const QString & textContent);
	void	onLoadFinished(bool ok);
	void	onLoadProgress(int progress);
	void	onLoadStarted();
	//void	onMenuBarVisibilityChangeRequested(bool visible);
	//void	onMicroFocusChanged();
	void	onPrintRequested(QWebFrame * frame);
	//void	onRepaintRequested(const QRect & dirtyRect);
	//void	onRestoreFrameStateRequested(QWebFrame * frame);
	//void	onSaveFrameStateRequested(QWebFrame * frame, QWebHistoryItem * item);
	//void	onScrollRequested(int dx, int dy, const QRect & rectToScroll);
	//void	onSelectionChanged();
	//void	onStatusBarMessage(const QString & text);
	//void	onStatusBarVisibilityChangeRequested(bool visible);
	//void	onToolBarVisibilityChangeRequested(bool visible);
	void	onUnsupportedContent(QNetworkReply * reply);

	virtual bool eventFilter(QObject *, QEvent *);

	virtual void customEvent(QEvent *);

	//void	onViewportChangeRequested();
	//void	onWindowCloseRequested();

};

#endif