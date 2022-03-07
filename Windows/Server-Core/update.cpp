#include "libCommon.h"
#include "update.h"
void update::updateCpuDiskNetwork(CPU* c, disks* d, network* n)
{
	HQUERY query;
	HCOUNTER pCounterHandle = nullptr;
	PDH_STATUS status = PdhOpenQuery(NULL, NULL, &query);
	
	HCOUNTER cpuUsage;
	HCOUNTER diskRead, diskWrite;
	HCOUNTER download, upload;

	status = PdhAddCounter(query, _TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuUsage); //%�ź�P֮��Ҫ�пո�
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
		throwError('u', 1, "��ʼ����������ʧ��.");
		return;
	}
	PdhCollectQueryData(query);
	Sleep(1000);  //����Ҫ����ʱ��Ȼ����൱��׼ȷ  
	PdhCollectQueryData(query);
	if (ERROR_SUCCESS != status)
	{
		throwError('u',2,"��������ʧ��.");
		return;
	}
	PDH_FMT_COUNTERVALUE pdhValue;
	DWORD dwValue;
	if (c != nullptr)
	{
		status = PdhGetFormattedCounterValue(cpuUsage, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		if (ERROR_SUCCESS != status)
		{
			throwError('u',3,"����CPUʹ����ʧ��.");
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
			throwError('u',4,"���´��̶�ȡ�ٶ�ʧ��.");
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
			throwError('u',5,"���´��̶�ȡ�ٶ�ʧ��.");
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
			throwError('u',6,"���������ٶ�ʧ��.");
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
			throwError('u',7, "�����ϴ��ٶ�ʧ��.");
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
		throwError('u', 8,"�رղ�ѯ���ʧ��.");
		return;
	}
}
