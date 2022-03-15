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
	running = true;
	while (true)
	{
		myUpdate->updateCpuDiskNetwork(myCPU, myDisks, myNetwork);//更新cpu usage；diskIO、read、write；download、upload
		mySystem->update(); //更新系统运行时间	
		myMemory->update();  //更新内存freeSpace、usage
		myDisks->update(myDisks->getQuantity()); //更新磁盘name、usage、totalSpace、freeSpace、uasge





		myUpdate->createDataLog(myCPU, myDisks, myMemory, myNetwork);
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


