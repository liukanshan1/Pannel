#ifndef MEMORY_H
#define MEMONY_H
class memory
{
public:
	memory();
	void updateBasicInfo();
	void update();
	double getUsage();
	int getTotalSpace();
	int getFreeSpace();

private:

	//��̬��Ϣ
	int totalSpace;
	//��̬��Ϣ
	int freeSpace;
	double usage;

};
#endif
