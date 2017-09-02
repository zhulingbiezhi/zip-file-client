#include "TCefHandle.h"
#include <QDebug>
#include <QDir>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

TCefHandle::TCefHandle(const QString& url, QWidget* parent) : QCefView(url, parent)
{
	installEventFilter(this);
}

TCefHandle::~TCefHandle()
{

}

void TCefHandle::processQCefUrlRequest(const QString& url)
{
	qDebug() << __FUNCTION__ << url;
	//throw std::logic_error("The method or operation is not implemented.");
}

void TCefHandle::processQCefQueryRequest(const QCefQuery& query)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void TCefHandle::onLoadStateChange(bool isLoading)
{
	qDebug() << __FUNCTION__ << isLoading;
	//throw std::logic_error("The method or operation is not implemented.");
}

void TCefHandle::onLoadStart()
{
	qDebug() << __FUNCTION__;
	//throw std::logic_error("The method or operation is not implemented.");
}

void TCefHandle::onLoadEnd(int httpStatusCode)
{
	qDebug() << __FUNCTION__ << httpStatusCode;
	//throw std::logic_error("The method or operation is not implemented.");	
}

void TCefHandle::onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl)
{
	qDebug() << __FUNCTION__ << errorCode << errorMsg << failedUrl;
}

void TCefHandle::onInvokeMethodNotify(const QString& method, const QVariantList& arguments)
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__ << method << arguments;
}

void TCefHandle::onUrlChange(const QString& url)
{
	//throw std::logic_error("The method or operation is not implemented.");
	qDebug() << __FUNCTION__ << url;
}

bool TCefHandle::excContextMenu(int id)
{
	//throw std::logic_error("The method or operation is not implemented.");
	switch (id)
	{
	case ECM_Back:
		this->browserGoBack();
		break;
	case ECM_Forward:
		this->browserGoForward();
		break;
	case ECM_Reload:
		this->browserReload();
		break;
	default:;
	}
	return true;
}

bool TCefHandle::getMenuInfo(int index, int& command, QString& lblName, bool& itemEnable)
{
	switch (index)
	{
	case 0:
		command = ECM_Back;
		lblName = tr("back");
		itemEnable = this->browserCanGoBack();
		return true;
	case 1:
		command = ECM_Forward;
		lblName = tr("forward");
		itemEnable = this->browserCanGoForward();
		return true;
	case 2:
		command = ECM_Reload;
		lblName = tr("reload");
		itemEnable = true;
		return true;
	default:
		command = -1;
		lblName = "";
		itemEnable = false;
		return false;
	}	
}

bool TCefHandle::eventFilter(QObject *obj, QEvent *e)
{
	//throw std::logic_error("The method or operation is not implemented.");
		switch (e->type())
		{
		case QEvent::Paint:
		case QEvent::Timer:
		case QEvent::MouseMove:
		case QEvent::ToolTipChange:
		case QEvent::UpdateLater:
			//ignore debug info of above events, see case default
			break;
// 		default:
// 			qDebug() << __FUNCTION__ << "TCefHandle  " << int(obj) << e->type() << winId();
		}

	return __super::eventFilter(obj, e);
}

void TCefHandle::onKeyEvent(const int& key)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

