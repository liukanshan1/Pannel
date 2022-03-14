#ifndef DISKS_H
#define DISKS_H
class disks
{
public:
	disks();
	~disks();

	void updateBasicInfo();
	void update(int quantity);
	friend void updateDisksIO(disks* d);

	int getQuantity();
	char getName(int n);
	int getUsage(int n);
	double getTotalSpace(int n);
	double getFreeSpace(int n);
	io getDiskIO();
	io getRead();
	io getWrite();
private:
	friend class update;
	//半动态信息
	int quantity;
	std::string name;
	int* usage;
	double* totalSpace;
	double* freeSpace;
	//动态信息
	io diskIO;
	io read;
	io write;
};
#endif
