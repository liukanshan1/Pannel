#ifndef CPU_H
#define CPU_H
class CPU
{
public:
	CPU();

	friend void updateCpuUsage(CPU* c);

	int getUsage();
	cpuInfo getInfo();
	std::string getDescription();

private:
	friend class update;
	void updateBasicInfo();
	void updateLogicalProcessorInfo();
	void updateCpuDiscription();
	DWORD CountSetBits(ULONG_PTR bitMask);
	//��̬��Ϣ
	int usage;
	//��̬��Ϣ
	cpuInfo info;
};
#endif