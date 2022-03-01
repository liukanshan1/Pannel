#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H
#include <string>
class operatingSystem
{
public:
	operatingSystem();
	void updateBasicInfo();
	std::string getName();
private:	
	std::string name;
};
#endif