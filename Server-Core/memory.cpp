#include"memory.h"
memory::memory()
{
    usage = 0;
    totalSpace = 0;
    freeSpace = 0;
    updateBasicInfo();
    update();
}
void memory::updateBasicInfo()
{
    //获取内存总容量
}
void memory::update()
{
    //获取内存剩余容量

    //计算usage

}

int memory::getUsage()
{
    return usage;
}
int memory::getFreeSpace()
{
    return freeSpace;
}
int memory::getTotalSpace()
{
    return totalSpace;
}