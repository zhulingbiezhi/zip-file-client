#include "TWebView.h"

#include <QDebug>

TWebView::TWebView()
: mstrPlayingUrl("")
{	
	qDebug() << __FUNCTION__;
}

TWebView::~TWebView()
{
	qDebug() << __FUNCTION__;
}
