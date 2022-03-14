#include "CPU.h"
#include "disks.h"
#include "network.h"
#include "memory.h"
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
	void setNetBestIndex(network* n, int i);
	void setNetSpeedIndex(network* n, int i);
	//设置阈值报警数值
	void setDiskUsageWarning(int i);
	void setMemoryUsageWarning(int i);
	void setCpuUsageWarning(int i);
	void setDiskIOWarning(io i);
	void setDiskReadWarning(io i);
	void setDiskWriteWarning(io i);
	void setNetIOWarning(io i);
	void setNetUploadWarning(io i);
	void setNetDownloadWarning(io i);
	//阈值报警开关
	void setDiskUsageWarning(bool i);
	void setMemoryUsageWarning(bool i);
	void setCpuUsageWarning(bool i);
	void setDiskIOWarning(bool i);
	void setDiskReadWarning(bool i);
	void setDiskWriteWarning(bool i);
	void setNetIOWarning(bool i);
	void setNetUploadWarning(bool i);
	void setNetDownloadWarning(bool i);
	//阈值报警
	void diskUsageWarning(disks* d);
	void memoryUsageWarning(memory* m);
	void cpuUsageWarning(CPU* c);
	void diskIOWarning(disks* d);
	void diskReadWarning(disks* d);
	void diskWriteWarning(disks* d);
	void netIOWarning(network* n);
	void netUploadWarning(network* n);
	void netDownloadWarning(network* n);
private:
	friend void createLogs(char type, std::string description);
	//日志开关
	bool enableLog = true;
	bool enableDataLog = true;
	//阈值报警开关
	bool enableDiskUsageWarning = false;
	bool enableMemoryUsageWarning = false;
	bool enableCpuUsageWarning = false;
	bool enableDiskIOWarning = false;
	bool enableDiskReadWarning = false;
	bool enableDiskWriteWarning = false;
	bool enableNetIOWarning = false;
	bool enableNetUploadWarning = false;
	bool enableNetDownloadWarning = false;
	//阈值报警数值
	int diskUsage = -1;
	int memoryUsage = -1;
	int cpuUsage = -1;
	io diskIO;
	io diskRead;
	io diskWrite;
	io netIO;
	io netUpload;
	io netDownload;
}myUpdate;
#endif
