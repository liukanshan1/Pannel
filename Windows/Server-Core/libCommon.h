//����������⹫�����������֣������õ���ϵͳ��
#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <VersionHelpers.h>
#include <malloc.h> 
#include <tchar.h>
#include <sysinfoapi.h>
#include <ctime>
#include <vector>
#include <functional>
#include <fstream>

#define _WIN32_WINNT 0x0500

//��CPU.cpp�л��õ�
typedef BOOL(WINAPI* LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);

struct cpuInfo
{
	std::string discription;
	std::string architecture;
	int numaNodeQuantity;
	int processorPackageQuantity;
	int processorCoreQuantity;
	int logicalProcessorQuantity;
	int processorL1CacheQuantity;
	int processorL2CacheQuantity;
	int processorL3CacheQuantity;
};

void runTask(const wchar_t* fileName);
void openFile(const char* fileName, int& data);
void openFile(const char* fileName, std::string& data);
