#ifndef CPU_H
#define CPU_H
class CPU
{
public:
	CPU();
	void update();
	int getUsage();
	cpuInfo getInfo();
private:
	void updateBasicInfo();
	void updateLogicalProcessorInfo();
	void updateCpuUsage();
	void updateCpuDiscription();
	//��̬��Ϣ
	int usage;
	//��̬��Ϣ
	cpuInfo info;
};
#endif