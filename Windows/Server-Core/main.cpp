#include "libCommon.h"
#include "classLib.h"



int main()
{
	operatingSystem s;
	std::cout << s.getVersion();
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