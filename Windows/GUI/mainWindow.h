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
	void deleteLogs();
	void deleteHistoryData();
	int enableLogChanged();
	int enableUpdateChanged();
	void setNetSpeedIndex(int i);
	int dataLogChanged();
	int diskUsageWarningChanged();
	int memoryUsageWarningChanged();
	int cpuUsageWarningChanged();
	void diskUsageLimit();
	void memoryUsageLimit();
	void cpuUsageLimit();
	void cpuUsageChanged(int usage);
	void diskIOchanged(io diskIO, io read, io write);
	void netUDchanged(io upload, io download);
	void diskUsageChanged(std::string name, std::string usage);
	void runningTimeChanged(runningTime t);
	void memoryUsageChanged(int usage, double freespace);
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


