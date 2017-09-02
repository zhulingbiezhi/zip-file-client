#ifndef _TWEBVIEWRENDER_H_
#define _TWEBVIEWRENDER_H_

#include <QWidget>
#include <QVBoxLayout>

class TWebViewRender : public QWidget
{
public:
	TWebViewRender();
	~TWebViewRender();
	void AddWidget(QWidget* pWidget);

private:


private:

	QVBoxLayout     *mplytMain;
};

#endif