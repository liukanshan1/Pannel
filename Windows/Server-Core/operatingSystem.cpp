#define _WIN32_WINNT 0x0500
#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
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
}
std::string operatingSystem::getName()
{
	return name;
}

//copy
//WCHAR* b;
//b = _wcsdup(buffer);
//_tprintf(TEXT("%s\n"), b);