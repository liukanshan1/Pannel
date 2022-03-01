#ifndef MEMORY_H
#define MEMONY_H
class memory
{
public:
	memory();
	void updateBasicInfo();
	void update();
	int getUsage();
	int getTotalSpace();
	int getFreeSpace();

private:

	//静态信息
	int totalSpace;
	//动态信息
	int freeSpace;
	int usage;

};
#endif
