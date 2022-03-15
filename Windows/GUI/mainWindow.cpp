#include "classLib.h"
#include "mainWindow.h"
#include "mainLoop.h"
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("监控面板"));

	QTabWidget* tabs = new QTabWidget(this);
	//ui.horizontalLayout->addWidget(tabs);
	
	//add page1
	QFrame* page1 = new QFrame(tabs);
	QHBoxLayout* h1 = new QHBoxLayout(page1);

	QLabel* labelName = new QLabel(page1);
	labelName->setText("姓名: ");
	h1->addWidget(labelName);

	QLineEdit* le1 = new QLineEdit(page1);
	h1->addWidget(le1);

	//add page2
	QFrame* page2 = new QFrame(tabs);
	QHBoxLayout* h2 = new QHBoxLayout(page2);

	QLabel* labelName2 = new QLabel(page2);
	labelName2->setText("性别: ");
	h2->addWidget(labelName2);

	QComboBox* cb2 = new QComboBox(page2);
	cb2->addItems(QStringList() << "男" << "女");
	h2->addWidget(cb2);

	tabs->addTab(page1, "姓名");
	tabs->addTab(page2, "性别");





	////菜单栏
	//QMenuBar* mBar = menuBar();
	////添加菜单
	//QMenu* overView = mBar->addMenu("概览");
	//QMenu* cpu = mBar->addMenu("CPU");
	//QMenu* disks = mBar->addMenu("磁盘");
	//QMenu* memory = mBar->addMenu("内存");
	//QMenu* network = mBar->addMenu("网络");
	//QMenu* systemInfo = mBar->addMenu("系统信息"); //操作系统和GPU
	//QMenu* settings = mBar->addMenu("设置");



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
