#ifndef CPU_H
#define CPU_H
class CPU
{
public:
	CPU();
	int getUsage();
	cpuInfo getInfo();
	std::string getDescription();
private:
	friend class update;
	void updateBasicInfo();
	void updateLogicalProcessorInfo();
	void updateCpuDiscription();
	DWORD CountSetBits(ULONG_PTR bitMask);
	//动态信息
	int usage;
	//静态信息
	cpuInfo info;
};
#endif