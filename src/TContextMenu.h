#ifndef _TCONTEXTMENU_H_
#define _TCONTEXTMENU_H_

#include<QFrame>
#include<QMenu>
#include<QAction>

class TContextMenu : public QFrame
{
	Q_OBJECT
public:
	TContextMenu(QWidget* parent = 0);
	~TContextMenu();

	void SetBackForwardState(bool bBack, bool bForward);
	
private:
	void CreateUI();
	void CreateConnect();

signals:
	void  sigBack(bool);
	void  sigForward(bool);
	void  sigReload(bool);

private:
	QMenu			*mpContextMenu;
	QAction			*mpBackAction;
	QAction			*mpForwardAction;
	QAction         *mpReloadAction;
};

#endif //_TCONTEXTMENU_H_