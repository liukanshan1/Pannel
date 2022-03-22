#include "CPU.h"
#include "disks.h"
#include "network.h"
#include "memory.h"
#include "libCommon.h"
#ifndef UPDATE_H
#define UPDATE_H
static class update
{
public:
	void updateCpuDiskNetwork(CPU* c, disks* d, network* n);
	void createDataLog(CPU* c, disks* d, memory* usage, network* n);
	//其他设置
	void setEnableLog(bool i);
	void setDataLog(bool i);
	//void setNetBestIndex(network* n, int i);
	void setNetSpeedIndex(network* n, int i);
	//设置阈值报警数值
	void setDiskUsageWarning(int i);
	void setMemoryUsageWarning(int i);
	void setCpuUsageWarning(int i);
	//阈值报警开关
	void setDiskUsageWarning(bool i);
	void setMemoryUsageWarning(bool i);
	void setCpuUsageWarning(bool i);
private:
	friend void createLogs(char type, std::string description);
	friend class mainLoop;
	//日志开关
	bool enableLog = true;
	bool enableDataLog = true;
	//阈值报警开关
	bool enableDiskUsageWarning = false;
	bool enableMemoryUsageWarning = false;
	bool enableCpuUsageWarning = false;
	//阈值报警数值
	int diskUsage = 100;
	int memoryUsage = 100;
	int cpuUsage = 100;
}myUpdate;
#endif
