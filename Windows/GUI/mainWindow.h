#include "libCommon.h"
#include "mainLoop.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
class mainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void stopLoop();
public:
    mainWindow(QWidget *parent = Q_NULLPTR);
    ~mainWindow();
private:
    Ui::mainWindowClass ui;
	CPU myCPU;
	disks myDisks;
	GPU myGPU;
	memory myMemory;
	network myNetwork;
	operatingSystem mySystem;
	mainLoop* loop = nullptr; 
};
#endif 


