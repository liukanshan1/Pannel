#ifndef MEMORY_H
#define MEMONY_H
class memory
{
public:
	memory();
	void updateBasicInfo();
	void update();
	int getUsage();
	double getTotalSpace();
	double getFreeSpace();
private:
	//��̬��Ϣ
	double totalSpace;
	//��̬��Ϣ
	double freeSpace;
	int usage;
};
#endif
