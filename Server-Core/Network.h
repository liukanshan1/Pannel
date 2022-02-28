#ifndef NETWORK_H
#define NETWORK_H
#include<string>
class network
{

public:
	network();
	~network();

	void updateBasicInfo();
	void update();

	int getQuantity();
	int getSpeed(int n);
	std::string getIPv4(int n);
	std::string getIPv6(int n);
	double getUsage(int n);
	int getUpload(int n);
	int getDownload(int n);

private:
	//静态数据
	int quantity;
	int* speed;
	std::string* IPv4;
	std::string* IPv6;
	//动态数据
	double* usage;
	int* upload;
	int* download;

};
#endif