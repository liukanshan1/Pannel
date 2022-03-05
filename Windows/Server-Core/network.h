#ifndef NETWORK_H
#define NETWORK_H
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
	int getUsage(int n);
	int getUpload(int n);
	int getDownload(int n);

private:
	friend class update;
	//静态数据
	int quantity;
	int* speed;
	std::string* IPv4;
	std::string* IPv6;
	//动态数据
	int* usage;
	int* upload;
	int* download;

};
#endif