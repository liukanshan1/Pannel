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
    //��ȡ�ڴ�������
}
void memory::update()
{
    //��ȡ�ڴ�ʣ������

    //����usage

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