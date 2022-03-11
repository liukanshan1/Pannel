#include "libCommon.h"
#include "classLib.h"

int main()
{
	//初始化
	createLogs('i', "初始化设备");
	CPU myCPU;
	disks myDisks;
	GPU myGPU;
	memory myMemory;
	network myNetwork;
	operatingSystem mySystem;


	//CPU info
	//int quantity;int* dedicatedVideoMemory;int* sharedSystemMemory; /std::string * info;
	//double totalSpace;
	//int quantity;bool* status;std::string* name;std::string* description;std::string* hardwareAddress;std::string* IPv4;std::string* IPv6;
	//std::string name;std::string version;	std::string checkVersion();
	while (true)
	{
		myUpdate.updateCpuDiskNetwork(&myCPU, &myDisks, &myNetwork); 
		/*cpu usage、
		diskIO;read;write;
		io getUpload();io getDownload();
		*/
		mySystem.update();
		//runningTime t;
		myMemory.update();
		//double freeSpace;int usage;


		//半动态信息
		//int quantity;std::string name;* usage;double* totalSpace;double* freeSpace;


	}






	myUpdate.createDataLog(&myCPU, &myDisks, &myMemory, &myNetwork);

	
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
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::fstream file;
		file.open(fileName, std::ios::app);
		file << "@echo off" << std::endl << "wmic cpu get name>>CpuDiscription";
		file.close();
	}
	else
	{
		file.close();
	}
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	if (CreateProcess(fileName, //位于工程所在目录下
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW, //这里不为该进程创建一个控制台窗口
		NULL,
		NULL,
		&si, &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE); //等待bat执行结束
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}
//void openFile(const char* fileName,int& data)
//{
//	std::fstream file(fileName);
//	data = -1;
//	if (!file.is_open())
//	{
//		return;
//	}
//	while (!file.eof())
//	{
//		file >> data;
//	}
//	//std::cout << data;
//	file.close();
//	std::fstream cleanFile(fileName, std::ios::out | std::ios::trunc);
//	cleanFile.close();
//}
void openCpuDiscription(const char* fileName, std::string& data)
{
	std::fstream file(fileName);
	if (!file.is_open())
	{

		throwError('m',1,"打开文件失败.");
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
	//for (int i = 0; i < data.length(); i++)
	//{
	//	std::cout << int(data[i]) << " " << data[i] << "\n";
	//}
	//std::cout << data << std::endl;
	file.close();
	std::fstream cleanFile(fileName, std::ios::out | std::ios::trunc);
	cleanFile.close();
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
		throwError('m',2,"字符串转换失败.");
	}
	return s;
}
std::string WStringToString(const std::wstring& wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}
wchar_t* stringToWCHAR(const std::string& str) //记得释放内存
{
	const char* pChar = str.c_str();
	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
	int len = MultiByteToWideChar(CP_OEMCP, 0, pChar, strlen(pChar) + 1, NULL, 0);
	wchar_t* pWCHAR = new wchar_t[len];
	//第二次调用将单字节字符串转换成双字节字符串
	MultiByteToWideChar(CP_OEMCP, 0, pChar, strlen(pChar) + 1, pWCHAR, len);
	return pWCHAR;
}
void updateCpuUsage(CPU* c)
{
	myUpdate.updateCpuDiskNetwork(c, nullptr, nullptr);
}
void updateDisksIO(disks* d)
{
	myUpdate.updateCpuDiskNetwork(nullptr, d, nullptr);
}
void updateNetworkUD(network* n)
{
	myUpdate.updateCpuDiskNetwork(nullptr, nullptr, n);
}
void throwError(char c, int location, std::string description) //TODO：allert函数
{
	int x;
	std::string temp = c + std::to_string(location) + ":" + description;
	temp[0] = toupper(temp[0]);
	WCHAR* p = stringToWCHAR(temp);
	//x = MessageBox(GetForegroundWindow(), p, L"错误", 1);
	if (p != nullptr)
	{
		delete p;
	}
	createLogs('e', temp);
}
void createLogs(char type, std::string description)
{
	if (myUpdate.enableLog)
	{
		time_t t;
		time(&t); //获取从1970至今过了多少秒
		tm currentTime;
		localtime_s(&currentTime, &t);
		std::string filename = std::to_string(currentTime.tm_year + 1900) + "." + std::to_string(currentTime.tm_mon + 1) + "." + std::to_string(currentTime.tm_mday);
		std::fstream file;
		_mkdir("log");
		file.open("log\\" + filename + ".log", std::ios::app);
		if (!file.is_open())
		{
			int x;
			x = MessageBox(GetForegroundWindow(), L"写入日志文件失败！", L"错误", 1);
			return;
		}
		file << std::to_string(currentTime.tm_year + 1900);
		file << (std::to_string(currentTime.tm_mon + 1).length() == 1)? ".0" : ".";
		file << std::to_string(currentTime.tm_mon + 1);
		file << (std::to_string(currentTime.tm_mday).length() == 1) ? ".0" : ".";
		file << std::to_string(currentTime.tm_mday);
		file << (std::to_string(currentTime.tm_hour).length() == 1) ? " 0" : " ";
		file << std::to_string(currentTime.tm_hour);
		file << (std::to_string(currentTime.tm_min).length() == 1) ? ":0" : ":";
		file << std::to_string(currentTime.tm_min) ;
		file << (std::to_string(currentTime.tm_sec).length() == 1) ? ":0" : ":";
		file << std::to_string(currentTime.tm_sec) << " ";;
		if (type == 'i')
		{
			file << "[info] ";
		}
		else if (type == 'a')
		{
			file << "[warning] ";
		}
		else if (type == 'e')
		{
			file << "[error] ";
		}
		file << description << std::endl;
		file.close();
	}
}
void deleteLog()
{
	if (_rmdir("log") == -1)
	{
		throwError('m', 3, "删除日志失败.");
	}
	else
	{
		createLogs('i', "删除日志成功");
	}
}
void deleteData()
{
	if (_rmdir("data") == -1)
	{
		throwError('m', 4, "删除数据记录失败.");
	}
	else
	{
		createLogs('i', "删除数据记录成功");
	}
}
