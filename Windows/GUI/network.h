#include "libCommon.h"
#ifndef NETWORK_H
#define NETWORK_H
class network
{

public:
	network();
	~network();

	friend void updateNetworkUD(network* n);

	int getQuantity();
	std::string getDescription(int n);
	std::string getHardwareAddress(int n);
	std::string getIPv4(int n);
	std::string getIPv6(int n);
	std::string getName(int n);
	bool getStatus(int n);
	io getUpload();
	io getDownload();

private:
	friend class update;
	friend class mainWindow;
	//静态数据
	int quantity;
	DWORD bestIndex;
	int* index;
	bool* status;
	std::string* name;
	std::string* description;
	std::string* hardwareAddress;
	std::string* IPv4;
	std::string* IPv6;
	int speedQuantity;
	int speedIndex;
	std::string* downloadPath;
	std::string* uploadPath;
	//动态数据
	io upload;
	io download;
};
#endif