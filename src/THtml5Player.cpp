#include "THtml5Player.h"
#include "TPlayerManager.h"
#include <QDebug>

THtml5Player::THtml5Player()
{
	mpPlayerManager = new TPlayerManager();
}

THtml5Player::~THtml5Player()
{
	if (mpPlayerManager)
	{
		delete mpPlayerManager;
	}
}

QWidget * THtml5Player::PlayItemShow(QString str, qint64 pos /*= 0*/)
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__;
	return 0;
}

void THtml5Player::DeleteItemElement()
{
	//throw std::logic_error("The method or operation is not implemented.");
	mpPlayerManager->clear();
	qDebug() << __FUNCTION__;
}

QStringList THtml5Player::getSupFmatList()
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__;
	QStringList supList;
	supList << "zip";
	return supList;
}

QWidget * THtml5Player::getPlayerWidget()
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__;
	return mpPlayerManager->getPlayerWidget();
}

bool THtml5Player::setSymmetricKey(PlayItem::SymEncryptionType type, const QByteArray &key, const QByteArray &iv)
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__;
	return mpPlayerManager->setSymmetricKey(type, key, iv);
}

bool THtml5Player::playFileOperator(File_Operator * pFileOperator, qint64 pos /*= 0*/)
{
	//throw std::logic_error("The method or operation is not implemented.");
	return mpPlayerManager->playFileOperator(pFileOperator, pos);
}

void THtml5Player::setPlayInfo(const QString &key, const QVariant &value1, const QVariant &value2 /*= QVariant()*/, const QVariant &value3 /*= QVariant()*/, const QVariant &value4 /*= QVariant()*/)
{
	//throw std::logic_error("The method or operation is not implemented.");
	return mpPlayerManager->setPlayInfo(key, value1, value2, value3, value4);
}

void THtml5Player::SetMprxHotAreaInfo(const QMap<int, CubicShapeMap> & shapeMap, const QImage & data, QString externInfo)
{
	return mpPlayerManager->SetMprxHotAreaInfo(shapeMap, data, externInfo);
}

bool THtml5Player::pause(bool bStop)
{
	if (bStop)
	{
		mpPlayerManager->pause(bStop);
	}
	return true;
}
