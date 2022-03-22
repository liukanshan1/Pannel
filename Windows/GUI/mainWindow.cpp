#include "mainWindow.h"
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("监控面板"));

	connect(ui.log, SIGNAL(stateChanged(int)), this, SLOT(enableLogChanged()));
	connect(ui.update, SIGNAL(stateChanged(int)), this, SLOT(enableUpdateChanged()));
	connect(ui.dataLog, SIGNAL(stateChanged(int)), this, SLOT(dataLogChanged()));
	connect(ui.cpu, SIGNAL(stateChanged(int)), this, SLOT(cpuUsageWarningChanged()));
	connect(ui.memory, SIGNAL(stateChanged(int)), this, SLOT(memoryUsageWarningChanged()));
	connect(ui.disk, SIGNAL(stateChanged(int)), this, SLOT(diskUsageWarningChanged()));
	connect(ui.cpuLimit, SIGNAL(editingFinished()), this, SLOT(cpuUsageLimit()));
	connect(ui.memoryLimit, SIGNAL(editingFinished()), this, SLOT(memoryUsageLimit()));
	connect(ui.diskLimit, SIGNAL(editingFinished()), this, SLOT(diskUsageLimit()));
	
	loop = new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
	//开始更新信息主循环
	loop->start();
	connect(this, SIGNAL(stopLoop()), loop, SLOT(stopLoop()));
	connect(loop, SIGNAL(sentCpuUsage(int)), this, SLOT(cpuUsageChanged(int)));
	connect(loop, SIGNAL(sentDiskIO(io)), this, SLOT(diskIOChanged(io)));
	connect(loop, SIGNAL(sentDiskRead(io)), this, SLOT(diskReadChanged(io)));
	connect(loop, SIGNAL(sentDiskWrite(io)), this, SLOT(diskWriteChanged(io)));
	connect(loop, SIGNAL(sentNetworkDownload(io)), this, SLOT(netDownloadChanged(io)));
	connect(loop, SIGNAL(sentNetworkUpload(io)), this, SLOT(netUploadChanged(io)));
	connect(loop, SIGNAL(sentRunningTime(runningTime)), this, SLOT(runningTimeChanged(runningTime)));
	connect(loop, SIGNAL(sentMemoryUsage(int,double)), this, SLOT(memoryUsageChanged(int , double)));
	connect(loop, SIGNAL(sentDiskUsage(int*,double*)), this, SLOT(diskUsageChanged(int* , double*)));

}
mainWindow::~mainWindow()
{
	if (loop != nullptr)
	{
		emit stopLoop();
		delete loop;
	}
}
int mainWindow::enableLogChanged()
{
	myUpdate.setEnableLog(ui.log->isChecked());
	return 0;
}
int mainWindow::dataLogChanged()
{
	myUpdate.setDataLog(ui.dataLog->isChecked());
	return 0;
}
int mainWindow::enableUpdateChanged()
{
	if (ui.update->isChecked())
	{
		emit stopLoop();
	}
	else
	{
		if (loop == nullptr)
		{
			loop = new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
		}
		loop->start();
		connect(this, SIGNAL(stopLoop()), loop, SLOT(stopLoop()));
	}
	return 0;
}
int mainWindow::diskUsageWarningChanged()
{
	myUpdate.setDiskUsageWarning(ui.disk->isChecked());
	return 0;
}
int mainWindow::memoryUsageWarningChanged()
{
	myUpdate.setMemoryUsageWarning(ui.memory->isChecked());
	return 0;
}
int mainWindow::cpuUsageWarningChanged()
{
	myUpdate.setCpuUsageWarning(ui.cpu->isChecked());
	return 0;
}
void mainWindow::diskUsageLimit()
{
	myUpdate.setDiskUsageWarning(ui.diskLimit->value());
}
void mainWindow::memoryUsageLimit()
{
	myUpdate.setMemoryUsageWarning(ui.memoryLimit->value());
}
void mainWindow::cpuUsageLimit()
{
	myUpdate.setCpuUsageWarning(ui.cpuLimit->value());
}


void mainWindow::cpuUsageChanged(int usage)
{
	//qDebug() << "A";
}
void mainWindow::diskIOChanged(io diskIO)
{

}
void mainWindow::diskReadChanged(io read)
{

}
void mainWindow::diskWriteChanged(io write)
{

}
void mainWindow::netDownloadChanged(io download)
{

}
void mainWindow::netUploadChanged(io upload)
{

}
void mainWindow::runningTimeChanged(runningTime t)
{

}
void mainWindow::memoryUsageChanged(int usage, double freespace)
{

}
void mainWindow::diskUsageChanged(int* usage, double* freeSpace)
{

}

//
//{
//
//		<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">
//		<html><head><meta name = "qrichtext" content = "1" / ><meta charset = "utf-8" / ><style type = "text/css">
//		p, li{ white - space: pre - wrap; }
//		< / style>< / head><body style = " font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;">
//		<p style = " margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">L3缓存：< / p>
//		< / body>< / html>
//}