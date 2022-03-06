#ifndef NETWORK_H
#define NETWORK_H
class network
{

public:
	network();
	~network();

	friend void updateNetworkUD(network* n);
	void setBestIndex(int n);
	void setSpeedIndex(int n);

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
	//��̬����
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
	//��̬����
	io upload;
	io download;
};
#endif