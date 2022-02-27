#ifndef TASK_H
#define TASK_H
#include <string>

class task
{
public:
	task();
	//更新信息
	void updateBasicInfo();
	void update();
	//返回信息
	std::string getName();
	int getPid();
	std::string getUser();
	std::string getFilePath();
	std::string getStatus();
	int getMemory();
	int getCPU();
	int getNetwork();
private:
	//静态信息
	std::string name;
	int pid;
	std::string user;
	std::string filePath;
	//动态信息
	std::string status;
	int memory;
	int CPU;
	int network;

};
#endif