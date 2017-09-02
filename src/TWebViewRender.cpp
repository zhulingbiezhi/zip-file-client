#include "TWebViewRender.h"
#include "TWebView.h"

#include <QDebug>
#include <QVBoxLayout>

TWebViewRender::TWebViewRender()
{
	mplytMain = new QVBoxLayout(this);
	mplytMain->setContentsMargins(0, 30, 0, 10);
}


TWebViewRender::~TWebViewRender()
{
	qDebug() << __FUNCTION__;
}

void TWebViewRender::AddWidget(QWidget* pWidget)
{
	mplytMain->addWidget(pWidget);
}
