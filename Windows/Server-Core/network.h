#ifndef NETWORK_H
#define NETWORK_H
class network
{

public:
	network();
	~network();

	friend void updateNetworkUD(network* n);

	int getQuantity();
	DWORD getBestIndex();
	std::string getDescription(int n);
	std::string getHardwareAddress(int n);
	std::string getIPv4(int n);
	std::string getIPv6(int n);
	std::string getName(int n);
	bool getStatus(int n);
	io getUpload(int n);
	io getDownload(int n);

private:
	friend class update;
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
	//动态数据
	io* upload;
	io* download;
};
#endif