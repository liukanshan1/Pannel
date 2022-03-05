#ifndef NETWORK_H
#define NETWORK_H
class network
{

public:
	network();
	~network();

	void updateBasicInfo();
	friend void updateNetworkUD(network* n);

	int getQuantity();
	DWORD getBestIndex();
	std::string getDescription(int n);
	std::string getHardwareAddress(int n);
	std::string getIPv4(int n);
	std::string getIPv6(int n);
	std::string getGatewayAddress(int n);
	dhcpInfo getDHCP(int n);
	io getUpload(int n);
	io getDownload(int n);

private:
	friend class update;
	//静态数据
	int quantity;
	DWORD bestIndex;
	std::string* description;
	std::string* hardwareAddress;
	std::string* IPv4;
	std::string* IPv6;
	std::string* gatewayAddress;
	dhcpInfo* dhcp;
	//动态数据
	io* upload;
	io* download;
};
#endif