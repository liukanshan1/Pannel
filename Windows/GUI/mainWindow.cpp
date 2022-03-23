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
	connect(this, SIGNAL(sentLog(std::string)), this, SLOT(updateLog(std::string)));
	connect(ui.netSpeedIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(setNetSpeedIndex(int)));
	connect(ui.deleteLog, SIGNAL(clicked()), this, SLOT(deleteLogs()));
	connect(ui.deleteData, SIGNAL(clicked()), this, SLOT(deleteHistoryData()));

	for (int i = 0; i < myNetwork.speedQuantity; i++)
	{
		ui.netSpeedIndex->addItem(QString::asprintf("%d", i));
	}
	ui.cpuData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.cpuDes->insertPlainText("描述：" + QString::fromStdString(myCPU.getInfo().discription));
	ui.cpuDes->insertPlainText("架构：" + QString::fromStdString(myCPU.getInfo().architecture) + "\n");
	ui.cpuDes->insertPlainText("NUMA节点数量：" + QString::number(myCPU.getInfo().numaNodeQuantity) + "\n");
	ui.cpuDes->insertPlainText("ProcessorPackage数量：" + QString::number(myCPU.getInfo().processorPackageQuantity) + "\n");
	ui.cpuDes->insertPlainText("逻辑处理器数量：" + QString::number(myCPU.getInfo().logicalProcessorQuantity) + "\n");
	ui.cpuDes->insertPlainText("处理器核心数量：" + QString::number(myCPU.getInfo().processorCoreQuantity) + "\n");
	ui.cpuDes->insertPlainText("L1缓存：" + QString::number(myCPU.getInfo().processorL1CacheQuantity) + "KB\n");
	ui.cpuDes->insertPlainText("L2缓存：" + QString::number(myCPU.getInfo().processorL2CacheQuantity) + "KB\n");
	ui.cpuDes->insertPlainText("L3缓存：" + QString::number(myCPU.getInfo().processorL3CacheQuantity) + "KB\n");
	ui.memData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.netSpeed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	for (int i = 0; i < myNetwork.getQuantity(); i++)
	{
		ui.netData->insertPlainText("网卡" + QString::number(i) + ":\n");
		ui.netData->insertPlainText("名称：" + QString(QString::fromLocal8Bit(myNetwork.getName(i).c_str())) + "\n");
		if (myNetwork.getStatus(i))
		{
			ui.netData->insertPlainText("已启用：是\n");
		}
		else
		{
			ui.netData->insertPlainText("已启用：否\n");
		}
		ui.netData->insertPlainText("描述：" + QString::fromStdString(myNetwork.getDescription(i)) + "\n");
		ui.netData->insertPlainText("硬件地址：" + QString::fromStdString(myNetwork.getHardwareAddress(i)) + "\n");
		if (myNetwork.getIPv4(i).length() != 0)
		{
			ui.netData->insertPlainText("IPv4：" + QString::fromStdString(myNetwork.getIPv4(i)) + "\n");
		}
		if (myNetwork.getIPv6(i).length() != 0)
		{
			ui.netData->insertPlainText("IPv6：" + QString::fromStdString(myNetwork.getIPv6(i)) + "\n");
		}
		ui.netData->insertPlainText("\n");
	}
	
	loop = new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
	connect(this, SIGNAL(stopLoop()), loop, SLOT(stopLoop()));
	connect(loop, SIGNAL(sentCpuUsage(int)), this, SLOT(cpuUsageChanged(int)));
	connect(loop, SIGNAL(sentDiskIO(io, io, io)), this, SLOT(diskIOchanged(io, io, io)));
	connect(loop, SIGNAL(sentNetworkUD(io, io)), this, SLOT(netUDchanged(io, io)));
	connect(loop, SIGNAL(sentRunningTime(runningTime)), this, SLOT(runningTimeChanged(runningTime)));
	connect(loop, SIGNAL(sentMemoryUsage(int, double)), this, SLOT(memoryUsageChanged(int, double)));
	connect(loop, SIGNAL(sentDiskUsage(std::string, std::string)), this, SLOT(diskUsageChanged(std::string, std::string)));
	loop->start();
	

}
mainWindow::~mainWindow()
{
	if (loop != nullptr)
	{
		emit stopLoop();
		delete loop;
	}
}

void mainWindow::deleteLogs()
{
	QMessageBox::StandardButton result = QMessageBox::information(NULL, "警告", "是否删除日志？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (result == QMessageBox::Yes)
	{
		emit stopLoop();
		deleteLog();
		if (loop == nullptr)
		{
			loop = new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
		}
		loop->start();
		connect(this, SIGNAL(stopLoop()), loop, SLOT(stopLoop()));
	}
}
void mainWindow::deleteHistoryData()
{
	QMessageBox::StandardButton result = QMessageBox::information(NULL, "警告", "是否删除历史数据？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (result == QMessageBox::Yes)
	{
		emit stopLoop();
		deleteData();
		if (loop == nullptr)
		{
			loop = new mainLoop(nullptr, &myCPU, &myDisks, &myMemory, &myNetwork, &mySystem, &myUpdate);
		}
		loop->start();
		connect(this, SIGNAL(stopLoop()), loop, SLOT(stopLoop()));
	}
}
void mainWindow::setNetSpeedIndex(int i)
{
	myUpdate.setNetSpeedIndex(&myNetwork, i);
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
void mainWindow::diskIOchanged(io diskIO, io read, io write)
{
	QString i, r, w;
	i += QString::number(diskIO.speed);
	r += QString::number(read.speed);
	w += QString::number(write.speed);
	switch (diskIO.unit)
	{
	case 0:
		i += "B/s";
		break;
	case 10:
		i += "K/s";
		break;
	case 100:
		i += "M/s";
		break;
	case 1000:
		i += "G/s";
		break;
	case 10000:
		i += "T/s";
		break;
	}
	switch (read.unit)
	{
	case 0:
		r += "B/s";
		break;
	case 10:
		r += "K/s";
		break;
	case 100:
		r += "M/s";
		break;
	case 1000:
		r += "G/s";
		break;
	case 10000:
		r += "T/s";
		break;
	}
	switch (write.unit)
	{
	case 0:
		w += "B/s";
		break;
	case 10:
		w += "K/s";
		break;
	case 100:
		w += "M/s";
		break;
	case 1000:
		w += "G/s";
		break;
	case 10000:
		w += "T/s";
		break;
	}
	ui.diskIO->setText("磁盘I/O：" + i);
	ui.diskRead->setText("磁盘读取速度：" + r);
	ui.diskWrite->setText("磁盘写入速度：" + w);
}
void mainWindow::netUDchanged(io upload, io download)
{
	ui.netSpeed->clear();
	QString u, d;
	u += QString::number(upload.speed);
	d += QString::number(download.speed);
	switch (upload.unit)
	{
	case 0:
		u += "B/s";
		break;
	case 10:
		u += "K/s";
		break;
	case 100:
		u += "M/s";
		break;
	case 1000:
		u += "G/s";
		break;
	case 10000:
		u += "T/s";
		break;
	}
	switch (download.unit)
	{
	case 0:
		d += "B/s";
		break;
	case 10:
		d += "K/s";
		break;
	case 100:
		d += "M/s";
		break;
	case 1000:
		d += "G/s";
		break;
	case 10000:
		d += "T/s";
		break;
	}
	ui.netSpeed->insertPlainText("下载速度：" + d + "\n");
	ui.netSpeed->insertPlainText("上传速度：" + u);
}
void mainWindow::diskUsageChanged(std::string name, std::string usage)
{
	int* p = new int[myDisks.getQuantity()];
	std::string temp;
	int i = 0;
	while (usage.length() != 0)
	{
		if (usage[0] != '/')
		{
			temp += usage[0];
			usage.erase(0, 1);
		}
		else
		{
			usage.erase(0, 1);
			p[i] = stoi(temp);
			temp.erase(0);
			i++;
		}
	}
		ui.diskInfo->clear();
	for (int i = 0; i < myDisks.getQuantity(); i++)
	{
		std::string temp(name, i, 1);
		ui.diskInfo->insertPlainText("盘符：" + QString::fromStdString(temp)+ "\n");
		ui.diskInfo->insertPlainText("占用率：" + QString::number(p[i]) + "%\n");
		ui.diskInfo->insertPlainText("总容量：" + QString::number(myDisks.getTotalSpace()[i]) + "GB\n");
		ui.diskInfo->insertPlainText("剩余容量：" + QString::number(myDisks.getTotalSpace()[i]*0.01* p[i]) + "GB\n");
		ui.diskInfo->insertPlainText("\n");
	}
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
void mainWindow::logChanged(std::string s)
{
	emit sentLog(s);
}
void mainWindow::updateLog(std::string s)
{
	ui.showLog->insertPlainText(QString::fromStdString(s) + "\n");
	ui.showLog->moveCursor(QTextCursor::End);
}
