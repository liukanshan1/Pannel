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
	//��̬����
	std::string name;
	std::string version;
	std::string checkVersion();
	//��̬����
	std::string runningTime;
};
#endif