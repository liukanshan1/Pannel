#ifndef CPU_H
#define CPU_H
#include<string>
class CPU
{
public:
	CPU();
	//更新信息
	void updateBasicInfo();
	void update();
	//返回信息
	int getUsage();
	int getCore();
	std::string getInfo();
	int getSpeed();
	std::string getArchitecture();
private:
	//动态信息
	int usage;
	int speed;
	//静态信息
	int core;
	std::string info;
	std::string architecture;
};
#endif