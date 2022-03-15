#include "update.h"

void update::updateCpuDiskNetwork(CPU* c, disks* d, network* n)
{
	createLogs('i', "更新CPU使用率、磁盘I/O、网络速度");
	HQUERY query;
	HCOUNTER pCounterHandle = nullptr;
	PDH_STATUS status = PdhOpenQuery(NULL, NULL, &query);
	
	HCOUNTER cpuUsage;
	HCOUNTER diskRead, diskWrite;
	HCOUNTER download, upload;

	status = PdhAddCounter(query, _TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuUsage); //%号和P之间要有空格
	status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"), NULL, &diskRead);
	status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Write Bytes/sec"), NULL, &diskWrite);
	if (n != nullptr)
	{
		status = PdhAddCounterA(query, n->downloadPath[n->speedIndex].c_str(), NULL, &download);
		status = PdhAddCounterA(query, n->uploadPath[n->speedIndex].c_str(), NULL, &upload);
	}
	else
	{
		status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"), NULL, &download);
		status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"), NULL, &upload);
	}
	
	if (ERROR_SUCCESS != status)
	{
		throwError('u', 1, "初始化更新数据失败.");
		return;
	}
	PdhCollectQueryData(query);
	Sleep(1000);  //这里要有延时不然结果相当不准确  
	PdhCollectQueryData(query);
	if (ERROR_SUCCESS != status)
	{
		throwError('u',2,"更新数据失败.");
		return;
	}
	PDH_FMT_COUNTERVALUE pdhValue;
	DWORD dwValue;
	if (c != nullptr)
	{
		status = PdhGetFormattedCounterValue(cpuUsage, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',3,"更新CPU使用率失败.");
			return;
		}
		else
		{
			double temp = pdhValue.doubleValue;
			c->usage = (int)(temp + 0.5);
		}
		PdhRemoveCounter(cpuUsage);
	}
	if (d != nullptr)
	{
		long long int ioTemp = 0;
		status = PdhGetFormattedCounterValue(diskRead, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',4,"更新磁盘读取速度失败.");
			return;
		}
		else
		{
			double temp = pdhValue.doubleValue;
			int read = (double)((temp / (1024 * 1.0f)));
			ioTemp += read;
			if (read > (1024 * 1024))
			{
				read /= (1024 * 1024);
				d->read.speed = read;
				d->read.unit = gb;
			}
			else if (read > 1024)
			{
				read /= 1024;
				d->read.speed = read;
				d->read.unit = mb;
			}
			else
			{
				d->read.speed = read;
				d->read.unit = kb;
			}
		}
		status = PdhGetFormattedCounterValue(diskWrite, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',5,"更新磁盘读取速度失败.");
			return;
		}
		else
		{
			double temp = pdhValue.doubleValue;
			int write = (double)((temp / (1024 * 1.0f)));
			ioTemp += write;
			if (write > (1024 * 1024))
			{
				write /= (1024 * 1024);
				d->write.speed = write;
				d->write.unit = gb;
			}
			else if (write > 1024)
			{
				write /= 1024;
				d->write.speed = write;
				d->write.unit = mb;
			}
			else
			{
				d->write.speed = write;
				d->write.unit = kb;
			}
		}
		if (ioTemp > (1024 * 1024))
		{
			ioTemp /= (1024 * 1024);
			d->diskIO.speed = ioTemp;
			d->diskIO.unit = gb;
		}
		else if (ioTemp > 1024)
		{
			ioTemp /= 1024;
			d->diskIO.speed = ioTemp;
			d->diskIO.unit = mb;
		}
		else
		{
			d->diskIO.speed = ioTemp;
			d->diskIO.unit = kb;
		}
		PdhRemoveCounter(diskRead);
		PdhRemoveCounter(diskWrite);
	}
	if (n != nullptr)
	{
		status = PdhGetFormattedCounterValue(download, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',6,"更新下载速度失败.");
			return;
		}
		else
		{
			double temp = pdhValue.doubleValue;
			int receive = (double)((temp / (1024 * 1.0f)));
			if (receive > (1024 * 1024))
			{
				receive /= (1024 * 1024);
				n->download.speed = receive;
				n->download.unit = gb;
			}
			else if (receive > 1024)
			{
				receive /= 1024;
				n->download.speed = receive;
				n->download.unit = mb;
			}
			else
			{
				n->download.speed = receive;
				n->download.unit = kb;
			}
		}
		status = PdhGetFormattedCounterValue(upload, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',7, "更新上传速度失败.");
			return;
		}
		else
		{
			double temp = pdhValue.doubleValue;
			int sent = (double)((temp / (1024 * 1.0f)));
			if (sent > (1024 * 1024))
			{
				sent /= (1024 * 1024);
				n->upload.speed = sent;
				n->upload.unit = gb;
			}
			else if (sent > 1024)
			{
				sent /= 1024;
				n->upload.speed = sent;
				n->upload.unit = mb;
			}
			else
			{
				n->upload.speed = sent;
				n->upload.unit = kb;
			}
		}
		PdhRemoveCounter(download);
		PdhRemoveCounter(upload);
	}
	PdhCloseQuery(query);
	if (status != ERROR_SUCCESS)
	{
		throwError('u', 8,"关闭查询句柄失败.");
		return;
	}
}
void update::createDataLog(CPU* c, disks* d, memory* m, network* n) 
{
	if (myUpdate.enableDataLog)
	{
		time_t t;
		time(&t); //获取从1970至今过了多少秒
		tm currentTime;
		localtime_s(&currentTime, &t);
		std::string filename = std::to_string(currentTime.tm_year + 1900) + "." + std::to_string(currentTime.tm_mon + 1) + "." + std::to_string(currentTime.tm_mday);
		std::fstream file;
		_mkdir("data");
		/*if (_mkdir("data") == -1)
		{
			throwError('u', 21, "创建数据记录文件夹失败.");
		}
		else
		{
			createLogs('i', "创建数据记录文件夹.");
		}*/
		file.open("data\\" + filename + ".csv", std::ios::app);
		if (!file.is_open())
		{
			throwError('u', 9, "写入数据文件失败.");
			return;
		}
		file << std::to_string(currentTime.tm_year + 1900);
		file << (std::to_string(currentTime.tm_mon + 1).length() == 1) ? ",0" : ",";
		file << std::to_string(currentTime.tm_mon + 1);
		file << (std::to_string(currentTime.tm_mday).length() == 1) ? ",0" : ",";
		file << std::to_string(currentTime.tm_mday);
		file << (std::to_string(currentTime.tm_hour).length() == 1) ? ",0" : ",";
		file << std::to_string(currentTime.tm_hour);
		file << (std::to_string(currentTime.tm_min).length() == 1) ? ",0" : ",";
		file << std::to_string(currentTime.tm_min);
		file << (std::to_string(currentTime.tm_sec).length() == 1) ? ",0" : ",";
		file << std::to_string(currentTime.tm_sec) << ",";;
		file << c->usage << ","
			<< d->diskIO.speed << ","
			<< d->diskIO.unit << ","
			<< d->read.speed << ","
			<< d->read.unit << ","
			<< d->write.speed << ","
			<< d->write.unit << ","
			<< m->usage << ","
			<< n->upload.speed << ","
			<< n->upload.unit << ","
			<< n->download.speed << ","
			<< n->download.unit << std::endl;
		file.close();
	}
}
//年，月，日，时，分，秒，
//CPU使用率，
//磁盘IO，磁盘IO单位（2的多少次方），磁盘读取，磁盘读取单位，磁盘写入，磁盘写入单位，
//内存使用率，
//网络上传速率，网络上传单位，网络下载速率，网络下载单位

//其他设置
void update::setNetBestIndex(network* n, int i)
{
	if (i >= 0 && i < n->quantity)
	{
		n->bestIndex = i;
	}
	else
	{
		throwError('u', 10, "请输入正确的值.");
	}
}
void update::setNetSpeedIndex(network* n, int i)
{
	if (i >= 0 && i < n->speedQuantity)
	{
		n->speedIndex = i;
	}
	else
	{
		throwError('u', 11, "请输入正确的值.");
	}
}
void update::setEnableLog(bool i)
{
	enableLog = i;
}
void update::setDataLog(bool i)
{
	enableDataLog = i;
}
//设置报警阈值
void update::setDiskUsageWarning(int i)
{
	if (i > 0 && i <= 100)
	{
		diskUsage = i;
	}
	else
	{
		throwError('u', 12, "请输入正确的值.");
	}
}
void update::setMemoryUsageWarning(int i)
{
	if (i > 0 && i <= 100)
	{
		memoryUsage = i;
	}
	else
	{
		throwError('u', 13, "请输入正确的值.");
	}
}
void update::setCpuUsageWarning(int i)
{
	if (i > 0 && i <= 100)
	{
		cpuUsage = i;
	}
	else
	{
		throwError('u', 14, "请输入正确的值.");
	}
}
void update::setDiskIOWarning(io i)
{
	if (i.speed>0)
	{
		diskIO = i;
	}
	else
	{
		throwError('u', 15, "请输入正确的值.");
	}
}
void update::setDiskReadWarning(io i)
{
	if (i.speed > 0)
	{
		diskRead = i;
	}
	else
	{
		throwError('u', 16, "请输入正确的值.");
	}
}
void update::setDiskWriteWarning(io i)
{
	if (i.speed > 0)
	{
		diskWrite = i;
	}
	else
	{
		throwError('u', 17, "请输入正确的值.");
	}
}
void update::setNetIOWarning(io i)
{
	if (i.speed > 0)
	{
		netIO = i;
	}
	else
	{
		throwError('u', 18, "请输入正确的值.");
	}
}
void update::setNetUploadWarning(io i)
{
	if (i.speed > 0)
	{
		netUpload = i;
	}
	else
	{
		throwError('u', 19, "请输入正确的值.");
	}
}
void update::setNetDownloadWarning(io i)
{
	if (i.speed > 0)
	{
		netDownload = i;
	}
	else
	{
		throwError('u', 20, "请输入正确的值.");
	}
}
//错误编码22（包含22）开始

//设置阈值报警开关
void update::setDiskUsageWarning(bool i)
{
	enableDiskUsageWarning = i;
}
void update::setMemoryUsageWarning(bool i)
{
	enableMemoryUsageWarning = i;
}
void update::setCpuUsageWarning(bool i)
{
	enableCpuUsageWarning = i;
}
void update::setDiskIOWarning(bool i)
{
	enableDiskIOWarning = i;
}
void update::setDiskReadWarning(bool i)
{
	enableDiskReadWarning = i;
}
void update::setDiskWriteWarning(bool i)
{
	enableDiskWriteWarning = i;
}
void update::setNetIOWarning(bool i)
{
	enableNetIOWarning = i;
}
void update::setNetUploadWarning(bool i)
{
	enableNetUploadWarning = i;
}
void update::setNetDownloadWarning(bool i)
{
	enableNetDownloadWarning = i;
}

//阈值报警 TODO 一定时间 解除提醒
void update::diskUsageWarning(disks* d)
{

}
void update::memoryUsageWarning(memory* m)
{

}

void update::cpuUsageWarning(CPU* c)
{

}
void update::diskIOWarning(disks* d)
{

}
void update::diskReadWarning(disks* d)
{

}
void update::diskWriteWarning(disks* d)
{

}
void update::netIOWarning(network* n)
{

}
void update::netUploadWarning(network* n)
{

}
void update::netDownloadWarning(network* n)
{

}