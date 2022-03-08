#include "CPU.h"
#include "disks.h"
#include "network.h"
#include "memory.h"
#ifndef UPDATE_H
#define UPDATE_H
class update
{
public:
	static void updateCpuDiskNetwork(CPU* c, disks* d, network* n);
	static void createDataLog(CPU* c, disks* d, memory* usage, network* n);
private:

};
#endif
