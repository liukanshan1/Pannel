#include "libCommon.h"
#ifndef MEMORY_H
#define MEMONY_H
class memory
{
public:
	memory();
	void updateBasicInfo();
	void update();
	int getUsage();
	double getTotalSpace();
	double getFreeSpace();
private:
	friend class update;
	//静态信息
	double totalSpace;
	//动态信息
	double freeSpace;
	int usage;
};
#endif
