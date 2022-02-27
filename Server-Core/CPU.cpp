#include <stdio.h>
#include <string>
#if WIN32
#include "windows.h"
#else
//#include "unistd.h"
#endif
#include "CPU.h"

CPU::CPU()
{
    updateBasicInfo();
    update();
}
void CPU::updateBasicInfo()
{
    //��ȡ��������
    #if WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        core_ = sysInfo.dwNumberOfProcessors;
    #else //linux
        //core = sysconf(_SC_NPROCESSORS_CONF); //��ȡ��ǰϵͳ������CPU�������������õ�
    #endif
    //��ȡCPU��Ϣ
    
    //��ȡCPU�ܹ�
}
void CPU::update()
{
    //��ȡCPU������
    
    //��ȡCPUƵ��

}
int CPU::getCore()
{
    return core;
}
std::string CPU::getInfo()
{
    return info;
}
std::string CPU::getArchitecture()
{
    return architecture;
}
int CPU::getSpeed()
{
    return speed;
}
int CPU::getUsage()
{
    return usage;
}