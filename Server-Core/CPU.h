#ifndef CPU_H
#define CPU_H
#include<string>
class CPU
{
public:
	CPU();
	//������Ϣ
	void updateBasicInfo();
	void update();
	//������Ϣ
	int getUsage();
	int getCore();
	std::string getInfo();
	int getSpeed();
	std::string getArchitecture();
private:
	//��̬��Ϣ
	int usage;
	int speed;
	//��̬��Ϣ
	int core;
	std::string info;
	std::string architecture;
};
#endif