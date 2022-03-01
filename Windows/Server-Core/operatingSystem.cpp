#define _WIN32_WINNT 0x0500
#include "libCommon.h"
#include "operatingSystem.h"

operatingSystem::operatingSystem()
{
	updateBasicInfo();
}
std::string tcharToString(TCHAR* str)
{
	std::string s;
	try
	{
		int iLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		char* chRtn = new char[iLen * sizeof(char)];
		WideCharToMultiByte(CP_ACP, 0, str, -1, chRtn, iLen, NULL, NULL);
		s = chRtn;
	}
	catch (std::exception e)
	{
	}
	return s;
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


