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
	//��̬��Ϣ
	int usage;
	//��̬��Ϣ
	cpuInfo info;
};
#endif