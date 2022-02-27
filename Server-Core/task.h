#ifndef TASK_H
#define TASK_H
#include <string>

class task
{
public:
	task();
	//������Ϣ
	void updateBasicInfo();
	void update();
	//������Ϣ
	std::string getName();
	int getPid();
	std::string getUser();
	std::string getFilePath();
	std::string getStatus();
	int getMemory();
	int getCPU();
	int getNetwork();
private:
	//��̬��Ϣ
	std::string name;
	int pid;
	std::string user;
	std::string filePath;
	//��̬��Ϣ
	std::string status;
	int memory;
	int CPU;
	int network;

};
#endif