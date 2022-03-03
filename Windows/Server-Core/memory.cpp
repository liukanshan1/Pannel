#include "libCommon.h"
#include"memory.h"
memory::memory()
{
    usage = -1;
    totalSpace = -1;
    freeSpace = -1;
    updateBasicInfo();
    update();
}
void memory::updateBasicInfo()
{
    //获取内存总容量
    MEMORYSTATUS ms;
    ::GlobalMemoryStatus(&ms);
    totalSpace = ms.dwTotalPhys / 1024.0 / 1024.0 / 1024.0;
}
void memory::update()
{
    MEMORYSTATUS ms;
    ::GlobalMemoryStatus(&ms);
    freeSpace = ms.dwAvailPhys / 1024.0 / 1024.0 / 1024.0;
    usage = ms.dwMemoryLoad;
}

int memory::getUsage()
{
    return usage;
}
double memory::getFreeSpace()
{
    return freeSpace;
}
double memory::getTotalSpace()
{
    return totalSpace;
}
