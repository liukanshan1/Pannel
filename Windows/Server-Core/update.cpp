﻿#include "libCommon.h"
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
	time_t t;
	time(&t); //获取从1970至今过了多少秒
	tm currentTime;
	localtime_s(&currentTime, &t);
	std::string filename = std::to_string(currentTime.tm_year + 1900) + "." + std::to_string(currentTime.tm_mon + 1) + "." + std::to_string(currentTime.tm_mday);
	std::fstream file;
	_mkdir("data");
	file.open("data\\" + filename + ".csv", std::ios::app);
	if (!file.is_open())
	{
		int x;
		x = MessageBox(GetForegroundWindow(), L"写入数据文件失败！", L"错误", 1);
		return;
	}
	file << std::to_string(currentTime.tm_year + 1900) << "," //TODO:补0。
		<< std::to_string(currentTime.tm_mon + 1) << ","
		<< std::to_string(currentTime.tm_mday) << ","
		<< std::to_string(currentTime.tm_hour) << ","
		<< std::to_string(currentTime.tm_min) << ","
		<< std::to_string(currentTime.tm_sec) << ",";
	file << c->usage << ","
		<<d->diskIO.speed<<","
		<<d->diskIO.unit<<","
		<<d->read.speed<<","
		<<d->read.unit<<","
		<<d->write.speed<<","
		<<d->write.unit<<","
		<<m->usage<<","
		<<n->upload.speed<<","
		<<n->upload.unit<<","
		<<n->download.speed<<","
		<<n->download.unit<<std::endl;
	file.close();
}
//年，月，日，时，分，秒，
//CPU使用率，
//磁盘IO，磁盘IO单位（2的多少次方），磁盘读取，磁盘读取单位，磁盘写入，磁盘写入单位，
//内存使用率，
//网络上传速率，网络上传单位，网络下载速率，网络下载单位