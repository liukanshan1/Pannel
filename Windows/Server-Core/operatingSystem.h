#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H
class operatingSystem
{
public:
	operatingSystem();
	void updateBasicInfo();
	std::string getName();
	std::string getVersion();
	std::string getRnningTime();
private:
	//静态数据
	std::string name;
	std::string version;
	std::string checkVersion();
	//动态数据
	std::string runningTime;
};
#endif