#ifndef _TPLAYERMANAGER_H_
#define _TPLAYERMANAGER_H_

#include <QWidget>
#include "playitem.h"

class TWebView;
class TWebViewRender;
//class THttpServer;
class TZipServer;

class TPlayerManager : public QObject
{
public:
	TPlayerManager();
	virtual ~TPlayerManager();

	QWidget * getPlayerWidget();

	bool setSymmetricKey(PlayItem::SymEncryptionType type, const QByteArray &key, const QByteArray &iv);

	bool playFileOperator(File_Operator * pFileOperator, qint64 pos = 0);

	void setPlayInfo(const QString &, const QVariant &, const QVariant & = QVariant(), const QVariant & = QVariant(), const QVariant & = QVariant());

	void SetMprxHotAreaInfo(const QMap<int, CubicShapeMap> & shapeMap, const QImage & data, QString externInfo);

	bool pause(bool);

	void clear();

private:
	bool  Play(File_Operator * pFileOperator, QString& strUrl);

private:
	TWebView						*mpWebView;
	TWebViewRender					*mpWebViewRender;
	//THttpServer						*mpHttpServer;
	TZipServer						*mpZipServer;
	QMap<QString, QString>			mmapPlayRecord;
	qint64						    mqSize;
	QString							mstrUuid;
	File_Operator					*mpFileOperator;
	bool						    mbPause;
};
#endif