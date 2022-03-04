#include "libCommon.h"
#include "GPU.h"
GPU::GPU()
{
	quantity = -1;

}
GPU::~GPU()
{

}

void GPU::updateBasicInfo()
{

}

int GPU::getQuantity()
{
	return quantity;
}
int GPU::getDedicatedVideoMemory(int n)
{
	return dedicatedVideoMemory[n];
}
int GPU::getDedicatedSystemMemory(int n)
{
	return dedicatedSystemMemory[n];
}
int GPU::getSharedSystemMemory(int n)
{
	return sharedSystemMemory[n];
}
std::string GPU::getInfo(int n)
{
	return info[n];
}