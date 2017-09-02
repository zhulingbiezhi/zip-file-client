#include "TContextMenu.h"
#include <QVBoxLayout>

TContextMenu::TContextMenu(QWidget* parent)
:QFrame(parent)
{
	mpContextMenu = new QMenu();
	CreateUI();
	CreateConnect();
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

	setFixedSize(110, 90);
}

TContextMenu::~TContextMenu()
{

}

void TContextMenu::CreateUI()
{
// 	mpBackAction = new QAction(tr("web back"), mpContextMenu);
// 	mpForwardAction = new QAction(tr("web forward"), mpContextMenu);
// 	mpReloadAction = new QAction(tr("web reload"), mpContextMenu);
	
	mpContextMenu->setFixedSize(110, 90);

	mpContextMenu->addSeparator();
	mpBackAction = mpContextMenu->addAction(tr("web back"));
	mpContextMenu->addSeparator();
	mpForwardAction = mpContextMenu->addAction(tr("web forward"));
	mpContextMenu->addSeparator();
	mpReloadAction = mpContextMenu->addAction(tr("web reload"));
	mpContextMenu->addSeparator();

	QVBoxLayout*   pMainLyt = new QVBoxLayout();
	pMainLyt->setSpacing(0);
	pMainLyt->setMargin(0);
	pMainLyt->addWidget(mpContextMenu);
	this->setLayout(pMainLyt);
}

void TContextMenu::CreateConnect()
{
	connect(mpBackAction, SIGNAL(triggered(bool)), this, SIGNAL(sigBack(bool)));
	connect(mpForwardAction, SIGNAL(triggered(bool)), this, SIGNAL(sigForward(bool)));
	connect(mpReloadAction, SIGNAL(triggered(bool)), this, SIGNAL(sigReload(bool)));
}

void TContextMenu::SetBackForwardState(bool bBack, bool bForward)
{
	mpBackAction->setEnabled(bBack);
	mpForwardAction->setEnabled(bForward);
}
