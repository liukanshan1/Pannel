#include "libCommon.h"
#include "classLib.h"

int main()
{
	disks s;
	//while (true)
	{
		//s.update();

		std::cout <<s.getTotalSpace(0)
			<<" "<<s.getFreeSpace(0)
			<<" "<< s.getUsage(0) 
			<<" "<< s.getQuantity()
		<<" "<< s.getName(0) << std::endl;
	}
	
	//IsWindows10OrGreater();
	/*getTime t;
	std::cout << t.getDate() << " " << t.getDay() << " " << t.getHour() << " " << t.getMin() << " "
		<< t.getMon() << " " << t.getSec() << " " << t.getTimeZone() << " " << t.getYear() << std::endl;*/

}

std::string operatingSystem::checkVersion() //在operatingSystem.cpp定义会报错
{
	if (IsWindowsServer())
	{
		return "Windows Server";
	}
	std::vector<std::function<bool()>> checkVersion;
	checkVersion.push_back(IsWindows10OrGreater);
	checkVersion.push_back(IsWindows8Point1OrGreater);
	checkVersion.push_back(IsWindows8OrGreater);
	checkVersion.push_back(IsWindows7SP1OrGreater);
	checkVersion.push_back(IsWindows7OrGreater);
	checkVersion.push_back(IsWindowsVistaSP2OrGreater);
	checkVersion.push_back(IsWindowsVistaSP1OrGreater);
	checkVersion.push_back(IsWindowsVistaOrGreater);
	checkVersion.push_back(IsWindowsXPSP3OrGreater);
	checkVersion.push_back(IsWindowsXPSP2OrGreater);
	checkVersion.push_back(IsWindowsXPSP1OrGreater);
	checkVersion.push_back(IsWindowsXPOrGreater);
	std::string versions[12] = { "Windows10或更高版本","Windows8.1","Windows8",
		"Windows7 SP1","Windows7","Vista SP2","Vista SP1","Vista",
		"WindowsXP SP3","WindowsXP SP2","WindowsXP SP1","WindowsXP"
	};
	std::string ver;
	for (int i = 0; i < 12; i++)
	{
		if (checkVersion[i]())
		{
			return versions[i];
		}
	}
}
void runTask(const wchar_t* fileName)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	if (CreateProcess(fileName,// 位于工程所在目录下
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,// 这里不为该进程创建一个控制台窗口
		NULL,
		NULL,
		&si, &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);// 等待bat执行结束
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}
void openFile(const char* fileName,int& data)
{
	std::fstream file(fileName);
	data = -1;
	if (!file.is_open())
	{
		return;
	}
	while (!file.eof())
	{
		file >> data;
	}
	//std::cout << data;
	file.close();
	std::fstream cleanFile(fileName, std::ios::out | std::ios::trunc);
	cleanFile.close();
}
void openFile(const char* fileName, std::string& data)
{
	std::fstream file(fileName);
	if (!file.is_open())
	{
		return;
	}
	std::string pre, now;
	while (!file.eof())
	{
		pre = now;
		getline(file, now);
	}
	//std::cout << pre << std::endl;
	data = pre;
	file.close();
	std::fstream cleanFile(fileName, std::ios::out | std::ios::trunc);
	cleanFile.close();
}