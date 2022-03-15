#include "libCommon.h"
#ifndef DISKS_H
#define DISKS_H
class disks
{
public:
	disks();
	~disks();

	void updateBasicInfo();
	void update(int quantity);
	friend void updateDisksIO(disks* d);

	int getQuantity();
	std::string getName();
	int* getUsage();
	double* getTotalSpace();
	double* getFreeSpace();
	io getDiskIO();
	io getRead();
	io getWrite();
private:
	friend class update;
	//半动态信息
	int quantity;
	std::string name;
	int* usage;
	double* totalSpace;
	double* freeSpace;
	//动态信息
	io diskIO;
	io read;
	io write;
};
#endif
