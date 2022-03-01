#ifndef CPU_H
#define CPU_H
#include<string>
struct cpuInfo
{
	std::string discription;
	std::string architecture;
	int numaNodeQuantity;
	int processorPackageQuantity;
	int processorCoreQuantity;
	int logicalProcessorQuantity;
	int processorL1CacheQuantity;
	int processorL2CacheQuantity;
	int processorL3CacheQuantity;
};
class CPU
{
public:
	CPU();
	void update();
	int getUsage();
	int getSpeed();
	cpuInfo getInfo();
private:
	void updateBasicInfo();
	void getLogicalProcessorInfo();
	//动态信息
	int usage;
	int speed;
	//静态信息
	cpuInfo info;
};
#endif