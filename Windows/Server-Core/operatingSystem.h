#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H
class operatingSystem
{
public:
	operatingSystem();
	void update();
	void updateBasicInfo();
	std::string getName();
	std::string getVersion();
	runningTime getRuningTime();
private:
	//��̬����
	std::string name;
	std::string version;
	std::string checkVersion();
	//��̬����
	runningTime t;
};
#endif