#include <string>
#include "network.h"
network::network()
{
	//��ȡ��������

	speed = new int[quantity];
	IPv4 = new std::string[quantity];
	IPv6 = new std::string[quantity];
	usage = new int[quantity];
	upload = new int[quantity];
	download = new int[quantity];
	updateBasicInfo();
	update();
}
void network::updateBasicInfo()
{

}
void network::update()
{

}
network::~network()
{
	//�ͷ��ڴ�
}
int network::getQuantity()
{
	return quantity;
}
int network::getSpeed(int n)
{
	return speed[n];
}
std::string network::getIPv4(int n)
{
	return IPv4[n];
}
std::string network::getIPv6(int n)
{
	return IPv6[n];
}
int network::getUsage(int n)
{
	return usage[n];
}
int network::getUpload(int n)
{
	return upload[n];
}
int network::getDownload(int n)
{
	return download[n];
}