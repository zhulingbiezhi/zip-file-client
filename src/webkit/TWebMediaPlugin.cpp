#include "TWebMediaPlugin.h"
#include <QDebug>
#include <QUrl>

TWebMediaPlugin::TWebMediaPlugin()
{
	qDebug() << __FUNCTION__;
}

TWebMediaPlugin::~TWebMediaPlugin()
{
	qDebug() << __FUNCTION__;
}

QList<QWebPluginFactory::Plugin> TWebMediaPlugin::plugins() const
{
	qDebug() << __FUNCTION__;
	QWebPluginFactory::MimeType mimeType;
	mimeType.name = "application/x-mplayer2";
	mimeType.description = QObject::tr("media");
	mimeType.fileExtensions.append(".flv");
	mimeType.fileExtensions.append(".f4v");
	mimeType.fileExtensions.append(".swf");
	mimeType.fileExtensions.append(".mp4");

	QList<QWebPluginFactory::MimeType> mimeTypeList;
	mimeTypeList.append(mimeType);

	QWebPluginFactory::Plugin plugin;
	plugin.name = QObject::tr("ldh flash plugin");
	plugin.description = QObject::tr("ldh flash plugin description");
	plugin.mimeTypes = mimeTypeList;

	QList<QWebPluginFactory::Plugin> pluginsList;
	pluginsList.append(plugin);
	return pluginsList;
}

QObject * TWebMediaPlugin::create(const QString& mimeType, const QUrl& url, const QStringList& argumentNames, const QStringList& argumentValues) const
{
	qDebug() << mimeType << url.toString();
	qDebug() << argumentNames;
	qDebug() << argumentValues;
	return NULL;
}
