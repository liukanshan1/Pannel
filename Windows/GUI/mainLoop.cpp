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
	std::vector<io>diskIO;
	std::vector<io>diskRead;
	std::vector<io>diskWrite;
	std::vector<io>netUpload;
	std::vector<io>netDownload;
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
		memoryUsage.push_back(myMemory->getUsage());
		cpuUsage.push_back(myCPU->getUsage());
		diskRead.push_back(myDisks->getRead());
		diskWrite.push_back(myDisks->getWrite());
		diskIO.push_back(myDisks->getDiskIO());
		netUpload.push_back(myNetwork->getUpload());
		netDownload.push_back(myNetwork->getDownload());


		QTime current_time = QTime::currentTime();
		int minute = current_time.minute();
		//5分钟平均负载
		bool flag5;
		if (minute / 5 == 0&&!flag5)
		{
			flag5 = true;
			int memoryUsageAver = 0;
			int cpuUsageAver = 0;
			io diskReadAver;
			io diskWriteAver;
			io diskIOAver;
			io netUploadAver;
			io netDownloadAver;
			if (myUpdate->enableDiskUsageWarning)
			{

			}
			if (myUpdate->enableMemoryUsageWarning)
			{
				while (memoryUsage.size() != 0)
				{
					memoryUsageAver += memoryUsage.back();
					memoryUsage.pop_back();
					if (memoryUsageAver != 0)
					{
						memoryUsageAver /= 2;
					}
				}
				if (memoryUsageAver >= myUpdate->memoryUsage)
				{
					emit memoryUsageWarning(memoryUsageAver, true);
				}
				else
				{
					emit memoryUsageWarning(memoryUsageAver, false);
				}
			}
			if (myUpdate->enableCpuUsageWarning)
			{
				while (cpuUsage.size() != 0)
				{
					cpuUsageAver += cpuUsage.back();
					cpuUsage.pop_back();
					if (cpuUsageAver != 0)
					{
						cpuUsageAver /= 2;
					}
				}
				if (cpuUsageAver >= myUpdate->cpuUsage)
				{
					emit cpuUsageWarning(cpuUsageAver, true);
				}
				else
				{
					emit cpuUsageWarning(cpuUsageAver, false);
				}
			}
			if (myUpdate->enableDiskIOWarning)
			{

			}
			if (myUpdate->enableDiskReadWarning)
			{

			}
			if (myUpdate->enableDiskWriteWarning)
			{

			}
			if (myUpdate->enableNetUploadWarning)
			{

			}
			if (myUpdate->enableNetDownloadWarning)
			{

			}
			memoryUsage.clear();
			cpuUsage.clear();
			diskRead.clear();
			diskWrite.clear();
			diskIO.clear();
			netUpload.clear();
			netDownload.clear();
			create5minLog(memoryUsageAver, cpuUsageAver, diskReadAver, diskWriteAver, diskIOAver, netUploadAver, netDownloadAver);
			//emit 
		}
		else
		{
			flag5 = false;
		}
		//20分钟平均负载
		bool flag20;
		if (minute / 20 == 0 && !flag20)
		{
			flag20 = true;



			//emit
		}
		else
		{
			flag20 = false;
		}
		//60分钟平均负载
		bool flag59;
		if (minute / 59 == 0 && !flag59)
		{
			flag59 = true;



			//emit
		}
		else
		{
			flag59 = false;
		}
		//昨天的平均负载



			//emit
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

void mainLoop::create5minLog(int memoryUsageAver,int cpuUsageAver,io diskReadAver,io diskWriteAver, io diskIOAver,io netUploadAver,io netDownloadAver)
{
		time_t t;
		time(&t); //获取从1970至今过了多少秒
		tm currentTime;
		localtime_s(&currentTime, &t);
		std::string filename = std::to_string(currentTime.tm_year + 1900) + "." + std::to_string(currentTime.tm_mon + 1) + "." + std::to_string(currentTime.tm_mday);
		std::fstream file;
		_mkdir("AverangeData");
		file.open("AverangeData\\" + filename + ".csv", std::ios::app);
		if (!file.is_open())
		{
			throwError('l', 1, "写入平均数据文件失败.");
			return;
		}
		file << std::to_string(currentTime.tm_year + 1900);
		file << ((std::to_string(currentTime.tm_mon + 1).length() == 1) ? ",0" : ",");
		file << std::to_string(currentTime.tm_mon + 1);
		file << ((std::to_string(currentTime.tm_mday).length() == 1) ? ",0" : ",");
		file << std::to_string(currentTime.tm_mday);
		file << ((std::to_string(currentTime.tm_hour).length() == 1) ? ",0" : ",");
		file << std::to_string(currentTime.tm_hour);
		file << ((std::to_string(currentTime.tm_min).length() == 1) ? ",0" : ",");
		file << std::to_string(currentTime.tm_min);
		file << ((std::to_string(currentTime.tm_sec).length() == 1) ? ",0" : ",");
		file << std::to_string(currentTime.tm_sec) << ",";
		file << cpuUsageAver << ","
			<< diskIOAver.speed << ","
			<< diskIOAver.unit << ","
			<< diskReadAver.speed << ","
			<< diskReadAver.unit << ","
			<< diskWriteAver.speed << ","
			<< diskWriteAver.unit << ","
			<< memoryUsageAver << ","
			<< netUploadAver.speed << ","
			<< netUploadAver.unit << ","
			<< netUploadAver.speed << ","
			<< netUploadAver.unit << std::endl;
		file.close();
}
//年，月，日，时，分，秒，
//CPU使用率，
//磁盘IO，磁盘IO单位（2的多少次方），磁盘读取，磁盘读取单位，磁盘写入，磁盘写入单位，
//内存使用率，
//网络上传速率，网络上传单位，网络下载速率，网络下载单位
