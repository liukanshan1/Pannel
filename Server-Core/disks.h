#ifndef DISKS_H
#define DISKS_H
#include <string>
class disks
{
public:
	disks();
	~disks();

	void updateBasicInfo(int quantity);
	void update(int quantity);

	int getQuantity();
	std::string getName(int n);
	std::string getType(int n);
	int getUsage(int n);
	int getTotalSpace(int n);
	int getFreeSpace(int n);
private:
	//静态信息
	int quantity;
	std::string* name;
	std::string* type;
	//动态信息
	int* usage;
	int* totalSpace;
	int* freeSpace;
};
#endif
