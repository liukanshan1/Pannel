#include "libCommon.h"
#include "operatingSystem.h"

operatingSystem::operatingSystem()
{
	updateBasicInfo();
}
void operatingSystem::updateBasicInfo()
{
	//获取计算机名称
    TCHAR buffer[256] = TEXT("");
    DWORD dwSize = _countof(buffer);
	if (!GetComputerNameEx(ComputerNamePhysicalDnsHostname, buffer, &dwSize))
	{
		//_tprintf(TEXT("GetComputerNameEx failed (%d)\n"), GetLastError());
		return;
	}
	else name = tcharToString(buffer);
    dwSize = _countof(buffer);
    ZeroMemory(buffer, dwSize);
	//获取Windows版本
	version = checkVersion();
}
std::string operatingSystem::getName()
{
	return name;
}
std::string operatingSystem::getVersion()
{
	return version;
}
std::string operatingSystem::getRnningTime()
{
	return runningTime;
}

//copy
//WCHAR* b;
//b = _wcsdup(buffer);
//_tprintf(TEXT("%s\n"), b);


