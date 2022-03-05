#include "libCommon.h"
#include "update.h"
void update::updateCpuDiskNetwork(CPU* c, disks* d, network* n)
{
	long long int ioTemp = 0;
	HQUERY query;
	HCOUNTER pCounterHandle = nullptr;
	PDH_STATUS status = PdhOpenQuery(NULL, NULL, &query);
	HCOUNTER cpuUsage;
	HCOUNTER diskRead, diskWrite;
	HCOUNTER download, upload;;


	status = PdhAddCounter(query, _TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuUsage); //%号和P之间要有空格
	status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"), NULL, &diskRead);
	status = PdhAddCounter(query, _TEXT("\\PhysicalDisk(_Total)\\Disk Write Bytes/sec"), NULL, &diskWrite);


	if (ERROR_SUCCESS != status)
	{
		return;
	}
	PdhCollectQueryData(query);
	Sleep(500);  //这里要有延时不然结果相当不准确  
	PdhCollectQueryData(query);
	if (ERROR_SUCCESS != status)
	{
		return;
	}
	PDH_FMT_COUNTERVALUE pdhValue;
	DWORD dwValue;
	if (c != nullptr)
	{
		status = PdhGetFormattedCounterValue(cpuUsage, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
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
		status = PdhGetFormattedCounterValue(diskRead, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
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

	}
	

	PdhCloseQuery(query);
	if (status != ERROR_SUCCESS)
	{
		return;
	}
}