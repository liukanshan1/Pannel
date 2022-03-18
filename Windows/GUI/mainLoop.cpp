#include "mainLoop.h"
mainLoop::mainLoop(QObject *parent, CPU* c, disks* d, memory* m, network* n, operatingSystem* o, update* u)
	: QThread(parent)
{
	myCPU = c;
	myDisks = d;
	myMemory = m;
	myNetwork = n;
	mySystem = o;
	myUpdate = u;
}
mainLoop::~mainLoop()
{
	stopLoop();
	this->deleteLater();
	this->wait();
}

void mainLoop::run()
{
	int diskQuantity = myDisks->getQuantity();
	running = true;
	std::vector<int>memoryUsage;
	std::vector<int>cpuUsage;
	bool flag5 = false;
	while (true)
	{
		myUpdate->updateCpuDiskNetwork(myCPU, myDisks, myNetwork);//更新cpu usage；diskIO、read、write；download、upload
		mySystem->update(); //更新系统运行时间	
		myMemory->update();  //更新内存freeSpace、usage
		myDisks->update(diskQuantity); //更新磁盘usage、totalSpace、freeSpace
		emit sentCpuUsage(myCPU->getUsage());
		emit sentDiskIO(myDisks->getDiskIO());
		emit sentDiskRead(myDisks->getRead());
		emit sentDiskWrite(myDisks->getWrite());
		emit sentNetworkDownload(myNetwork->getDownload());
		emit sentNetworkUpload(myNetwork->getUpload());
		emit sentRunningTime(mySystem->getRuningTime());
		emit sentMemoryUsage(myMemory->getUsage(), myMemory->getFreeSpace());
		emit sentDiskUsage(myDisks->getUsage(), myDisks->getFreeSpace());
		myUpdate->createDataLog(myCPU, myDisks, myMemory, myNetwork);
		//5分钟平均负载
		memoryUsage.push_back(myMemory->getUsage());
		cpuUsage.push_back(myCPU->getUsage());
		QTime current_time = QTime::currentTime();
		int minute = current_time.minute();
		if (minute / 5 == 0 && !flag5)
		{
			flag5 = true;
			int memoryUsageAver = 0;
			int cpuUsageAver = 0;
			if (myUpdate->enableDiskUsageWarning)
			{
				for (int i = 0; i < myDisks->getQuantity(); i++)
				{
					if (myDisks->usage[i] >= myUpdate->diskUsage)
					{
						emit diskUsageWarning(myDisks->name[i], myDisks->usage[i]);
					}
				}
			}
			//内存平均占用率计算
			while (memoryUsage.size() != 0)
			{
				memoryUsageAver += memoryUsage.back();
				memoryUsage.pop_back();
				if (memoryUsageAver != 0)
				{
					memoryUsageAver /= 2;
				}
			}
			if (myUpdate->enableMemoryUsageWarning)
			{
				if (memoryUsageAver >= myUpdate->memoryUsage)
				{
					emit memoryUsageWarning(memoryUsageAver, true);
				}
				else
				{
					emit memoryUsageWarning(memoryUsageAver, false);
				}
			}
			else
			{
				emit memoryUsageWarning(memoryUsageAver, false);
			}
			//CPU平均占用率计算
			while (cpuUsage.size() != 0)
			{
				cpuUsageAver += cpuUsage.back();
				cpuUsage.pop_back();
				if (cpuUsageAver != 0)
				{
					cpuUsageAver /= 2;
				}
			}
			if (myUpdate->enableCpuUsageWarning)
			{
				if (cpuUsageAver >= myUpdate->cpuUsage)
				{
					emit cpuUsageWarning(cpuUsageAver, true);
				}
				else
				{
					emit cpuUsageWarning(cpuUsageAver, false);
				}
			}
			else
			{
				emit cpuUsageWarning(cpuUsageAver, false);
			}
			memoryUsage.clear();
			cpuUsage.clear();
		}
		else
		{
			flag5 = false;
		}
		{
			QMutexLocker locker(&lock);
			if (!running)
			{
				return;
			}
		}
		
	}
}
void mainLoop::stopLoop()
{
	QMutexLocker locker(&lock);
	running = false;
}
