#include "libCommon.h"
#include "classLib.h"
#include "mainLoop.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
class mainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void stopLoop();
	void sentLog(std::string s);
public slots:
	int enableLogChanged();
	int enableUpdateChanged();
	int dataLogChanged();
	int diskUsageWarningChanged();
	int memoryUsageWarningChanged();
	int cpuUsageWarningChanged();
	void diskUsageLimit();
	void memoryUsageLimit();
	void cpuUsageLimit();
	void cpuUsageChanged(int usage);
	void diskIOChanged(io diskIO);
	void diskReadChanged(io read);
	void diskWriteChanged(io write);
	void netDownloadChanged(io download);
	void netUploadChanged(io upload);
	void runningTimeChanged(runningTime t);
	void memoryUsageChanged(int usage, double freespace);
	void diskUsageChanged(int* usage, double* freeSpace);
	void updateLog(std::string s);
public:
    mainWindow(QWidget *parent = Q_NULLPTR);
    ~mainWindow();
	void logChanged(std::string s);
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


