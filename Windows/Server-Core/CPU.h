#ifndef CPU_H
#define CPU_H
class CPU
{
public:
	CPU();
	void update();
	int getUsage();
	cpuInfo getInfo();
	std::string getDescription();
private:
	void updateBasicInfo();
	void updateLogicalProcessorInfo();
	void updateCpuUsage();
	void updateCpuDiscription();
	DWORD CountSetBits(ULONG_PTR bitMask);
	//动态信息
	int usage;
	//静态信息
	cpuInfo info;
};
#endif