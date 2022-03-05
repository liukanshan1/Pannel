#include "CPU.h"
#include "disks.h"
#include "network.h"
#ifndef UPDATE_H
#define UPDATE_H
class update
{
public:
	static void updateCpuDiskNetwork(CPU* c, disks* d, network* n);
private:

};
#endif
