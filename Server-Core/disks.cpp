#include <string>
#include "disks.h"
disks::disks()
{
	//��ȡ��������
	//quantity=?;

	//��ʼ������
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
	//���λ�ȡ��������

	//���λ�ȡ��������

}
void disks::update(int quantity)
{
	//���λ�ȡ����������

	//���λ�ȡ����ʣ������

	//���μ���ʹ����
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
	//�����ͷ��ڴ�
}