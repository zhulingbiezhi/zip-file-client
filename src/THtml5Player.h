#ifndef _THTML5PLAYER_H_
#define _THTML5PLAYER_H_

#include "playitem.h"

class TPlayerManager;

class THtml5Player : public PlayItem
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.HtmlPlugin/1.0")
	Q_INTERFACES(PlayItem)

public:
	THtml5Player();
	 ~THtml5Player();

	 QWidget * PlayItemShow(QString str, qint64 pos = 0);

	 bool pause(bool);

	 void DeleteItemElement();

	 QStringList getSupFmatList();

	 QWidget * getPlayerWidget();

	 bool setSymmetricKey(PlayItem::SymEncryptionType type, const QByteArray &key, const QByteArray &iv);

	 bool playFileOperator(File_Operator * pFileOperator, qint64 pos = 0);

	 void setPlayInfo(const QString &, const QVariant &, const QVariant & = QVariant(), const QVariant & = QVariant(), const QVariant & = QVariant());

	 void SetMprxHotAreaInfo(const QMap<int, CubicShapeMap> & shapeMap, const QImage & data, QString externInfo);

private:
	TPlayerManager				*mpPlayerManager;
};

#endif