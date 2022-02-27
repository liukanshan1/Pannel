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
    //获取核心数量
    #if WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        core_ = sysInfo.dwNumberOfProcessors;
    #else //linux
        //core = sysconf(_SC_NPROCESSORS_CONF); //获取当前系统的所有CPU核数，包含禁用的
    #endif
    //获取CPU信息
    
    //获取CPU架构
}
void CPU::update()
{
    //获取CPU利用率
    
    //获取CPU频率

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