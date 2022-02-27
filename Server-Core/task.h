#ifndef TASK_H
#define TASK_H
#include <string>

class task
{
public:
	task();

private:
	//¶¯Ì¬ĞÅÏ¢
	std::string name;
	int pid;
	std::string status;
	std::string user;
	int memory;
	std::string architecture;
	std::string description;
};
#endif