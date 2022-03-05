#include "libCommon.h"
#include "disks.h"
disks::disks()
{
	quantity = -1;
	usage = nullptr;
	totalSpace = nullptr;
	freeSpace = nullptr;
	updateBasicInfo();
	update(quantity);
}
disks::~disks()
{
	if (usage != nullptr)
	{
		delete[] usage;
	}
	if (totalSpace != nullptr)
	{
		delete[] totalSpace;
	}
	if (freeSpace != nullptr)
	{
		delete[] freeSpace;
	}
}

void disks::updateBasicInfo()
{
	int count = 0;
	quantity = 0;
	// ��ȡ��������
	DWORD diskQuantity = GetLogicalDrives();
	while (diskQuantity != 0)
	{
		if ((diskQuantity & 1) != 0)
		{
			name += char('A' + count);
			quantity++;
		}
		diskQuantity >>= 1;
		count++;
	}
	//��ʼ������
	usage = new int[quantity];
	totalSpace = new double[quantity];
	freeSpace = new double[quantity];
}
void disks::update(int quantity)
{
	//���λ�ȡ������������ʣ������������ʹ����
	for (int i = 0; i < quantity; i++)
	{
		wchar_t temp[4] = {name[i], ':','\\','\0'}; //'\\'ʵ������һ��\����һ��\��ת���ַ�
		const wchar_t* dir = temp;
		unsigned _int64 total, free;
		if (GetDiskFreeSpaceEx(dir, (PULARGE_INTEGER)&free, (PULARGE_INTEGER)&total,NULL))
		{

			totalSpace[i] = total / 1024.0 / 1024.0 / 1024.0;
			freeSpace[i] = free / 1024.0 / 1024.0 / 1024.0;
			usage[i] = 100 - free * 100 / total;
		}
	}
}

int disks::getQuantity()
{
	return quantity;
}
char disks::getName(int n)
{
	return name[n];
}
int disks::getUsage(int n)
{
	return usage[n];
}
double disks::getTotalSpace(int n)
{
	return totalSpace[n];
}
double disks::getFreeSpace(int n)
{
	return freeSpace[n];
}
io disks::getDiskIO()
{
	return diskIO;
}
io disks::getRead()
{
	return read;
}
io disks::getWrite()
{
	return write;
}

