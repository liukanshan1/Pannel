#include <string>
#include "disks.h"
disks::disks()
{
	//获取磁盘数量
	//quantity=?;

	//初始化变量
	name = new std::string[quantity];
	type = new std::string[quantity];
	usage = new int[quantity];
	totalSpace = new int[quantity];
	freeSpace = new int[quantity];
	updateBasicInfo(quantity);
	update(quantity);
}
void disks::updateBasicInfo(int quantity)
{
	//依次获取磁盘名称

	//依次获取磁盘类型

}
void disks::update(int quantity)
{
	//依次获取磁盘总容量

	//依次获取磁盘剩余容量

	//依次计算使用率
	//usage = freeSpace[] / totalSpace[];

}
int disks::getQuantity()
{
	return quantity;
}
std::string disks::getName(int n)
{
	return name[n];
}
std::string disks::getType(int n)
{
	return type[n];
}
int disks::getUsage(int n)
{
	return usage[n];
}
int disks::getTotalSpace(int n)
{
	return totalSpace[n];
}
int disks::getFreeSpace(int n)
{
	return freeSpace[n];
}

disks::~disks()
{
	//依次释放内存
}