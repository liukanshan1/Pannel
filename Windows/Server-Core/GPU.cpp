#include "libCommon.h"
#include "GPU.h"
GPU::GPU()
{
	//��ȡGPU����

	//��ʼ��
}
GPU::~GPU()
{

}

void GPU::updateBasicInfo()
{
	
}
void GPU::update()
{

}

int GPU::getUsage()
{
	return usage;
}
int GPU::getTotalGPUMemory()
{
	return totalGPUMemory;
}
int GPU::getUsingGPUMemory()
{
	return usingGPUMemory;
}
int GPU::getMemoryUsage()
{
	return usingGPUMemory;
}
int GPU::getQuantity()
{
	return quantity;
}
std::string GPU::getInfo()
{
	return info;
}