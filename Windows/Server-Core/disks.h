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
	io getDiskIO();
	io getRead();
	io getWrite();
private:
	friend class update;
	//�뾲̬��Ϣ
	int quantity;
	std::string name;
	//��̬��Ϣ
	int* usage;
	double* totalSpace;
	double* freeSpace;
	io diskIO;
	io read;
	io write;
};
#endif
