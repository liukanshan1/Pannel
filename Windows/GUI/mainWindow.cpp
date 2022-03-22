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
	
	ui.cpuData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.cpuDes->insertPlainText("L3缓存：" + QString::number(myCPU.getInfo().processorL3CacheQuantity) + "KB\n");
	ui.cpuDes->insertPlainText("L2缓存：" + QString::number(myCPU.getInfo().processorL2CacheQuantity) + "KB\n");
	ui.cpuDes->insertPlainText("L1缓存：" + QString::number(myCPU.getInfo().processorL1CacheQuantity) + "KB\n");
	ui.cpuDes->insertPlainText("逻辑处理器数量：" + QString::number(myCPU.getInfo().logicalProcessorQuantity) + "\n");
	ui.cpuDes->insertPlainText("处理器核心数量：" + QString::number(myCPU.getInfo().processorCoreQuantity) + "\n");
	ui.cpuDes->insertPlainText("ProcessorPackage数量：" + QString::number(myCPU.getInfo().processorPackageQuantity) + "\n");
	ui.cpuDes->insertPlainText("NUMA节点数量：" + QString::number(myCPU.getInfo().numaNodeQuantity) + "\n");
	ui.cpuDes->insertPlainText("架构：" + QString::fromStdString(myCPU.getInfo().architecture) + "\n");
	ui.cpuDes->insertPlainText("描述：" + QString::fromStdString(myCPU.getInfo().discription) + "\n");
	ui.memData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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
	ui.cpuData->clear();
	ui.cpuData->insertPlainText("占用率：" + QString::number(usage) + "%");
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
	ui.sysData->clear();
	ui.sysData->insertPlainText("电脑名称：" + QString::fromStdString(mySystem.getName()) + "\n");
	ui.sysData->insertPlainText("系统版本：" + QString::fromStdString(mySystem.getVersion()) + "\n");
	ui.sysData->insertPlainText("系统运行时间：" + QString::number(t.day) + ":" + QString::number(t.hour) + ":" + QString::number(t.min) + ":" + QString::number(t.sec));
}
void mainWindow::memoryUsageChanged(int usage, double freespace)
{
	ui.memData->clear();
	ui.memData->insertPlainText("占用率：" + QString::number(usage) + "%"+"\n");
	ui.memData->insertPlainText("总容量：" + QString::number(myMemory.getTotalSpace()) + "GB" + "\n");
	ui.memData->insertPlainText("剩余容量：" + QString::number(freespace) + "GB");
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