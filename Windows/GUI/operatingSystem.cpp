#include "libCommon.h"
#include "operatingSystem.h"

operatingSystem::operatingSystem()
{
	updateBasicInfo();
	update();
}
void operatingSystem::updateBasicInfo()
{
	//获取计算机名称
	createLogs('i', "获取计算机名称");
    TCHAR buffer[256] = TEXT("");
    DWORD dwSize = _countof(buffer);
	if (!GetComputerNameEx(ComputerNamePhysicalDnsHostname, buffer, &dwSize))
	{
		throwError('o',1,"GetComputerNameEx failed.");
		return;
	}
	else name = tcharToString(buffer);
    dwSize = _countof(buffer);
    ZeroMemory(buffer, dwSize);
	//获取Windows版本
	createLogs('i', "获取Windows版本");
	version = checkVersion();
}
void operatingSystem::update()
{
	//获取系统运行时间
	createLogs('i', "获取系统运行时间");
	t.sec = GetTickCount64() / 1000;
	if (t.sec >= 60)
	{
		t.min = t.sec / 60;
		t.sec %= 60;
	}
	if (t.min >= 60)
	{
		t.hour = t.min / 60;
		t.min %= 60;
	}
	if (t.hour >= 24)
	{
		t.day = t.hour / 24;
		t.hour %= 24;
	}
}
std::string operatingSystem::getName()
{
	return name;
}
std::string operatingSystem::getVersion()
{
	return version;
}
runningTime operatingSystem::getRuningTime()
{
	return t;
}

//copy
//WCHAR* b;
//b = _wcsdup(buffer);
//_tprintf(TEXT("%s\n"), b);


