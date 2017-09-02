#ifndef _TWEBMEDIAPLUGIN_H_
#define _TWEBMEDIAPLUGIN_H_

#include <QWebPluginFactory>
struct QWebPluginFactory::Plugin;

class TWebMediaPlugin : public QWebPluginFactory
{
	Q_OBJECT
public:
	TWebMediaPlugin();
	~TWebMediaPlugin();

	virtual QList<Plugin> plugins() const;

	virtual QObject * create(const QString& mimeType, const QUrl&, const QStringList& argumentNames, const QStringList& argumentValues) const;

protected:
	
private:

public slots :

signals:

private:

};
#endif