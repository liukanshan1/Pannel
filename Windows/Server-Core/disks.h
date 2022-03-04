#ifndef DISKS_H
#define DISKS_H
class disks
{
public:
	disks();
	~disks();

	void updateBasicInfo();
	void update(int quantity);

	int getQuantity();
	char getName(int n);
	int getUsage(int n);
	double getTotalSpace(int n);
	double getFreeSpace(int n);
	int getIO();
private:
	//半静态信息
	int quantity;
	std::string name;
	//动态信息
	int* usage;
	double* totalSpace;
	double* freeSpace;
	int io;
};
#endif
