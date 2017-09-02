#include "TCefView.h"

TCefView::TCefView(QWidget * parent)
: mpCefHandle(nullptr)
, mpParent(parent)
{
	
}

TCefView::~TCefView()
{

}

void TCefView::LoadPage(const QString& url)
{
	if (nullptr == mpCefHandle)
	{
		mpCefHandle = new TCefHandle(url, mpParent);
	}
	else
	{
		mpCefHandle->navigateToUrl(url);
	}	
}

void TCefView::Reload()
{
	mpCefHandle->browserReload();
}

void TCefView::Stop()
{
	mpCefHandle->browserStopLoad();
}

QWidget* TCefView::GetWebView()
{
	return mpCefHandle;
}

void TCefView::LoadBlank()
{
	//throw std::logic_error("The method or operation is not implemented.");
}
