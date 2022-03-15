#include "classLib.h"
#include "mainWindow.h"
#include "mainLoop.h"
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("监控面板"));



	////添加菜单项，添加动作
	//QAction* pNew = pFile->addAction("新建");
	//connect(pNew, &QAction::triggered,
	//	[=]()
	//	{
	//		emit stopLoop();
	//	}
	//);

	
	loop=new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
	//开始更新信息主循环
	loop->start();
	connect(this, &mainWindow::stopLoop, loop, &mainLoop::stopLoop);
	
	
}
mainWindow::~mainWindow()
{
	if (loop != nullptr)
	{
		emit stopLoop();
		delete loop;
	}
}
