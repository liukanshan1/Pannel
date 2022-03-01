#ifndef GPU_H
#define GPU_H
class GPU //！多个GPU的实现
{
public:
	GPU();
	~GPU();
	//更新信息
	void updateBasicInfo();
	void update();
	//返回信息
	int getUsage();
	int getTotalGPUMemory();
	int getUsingGPUMemory();
	int getMemoryUsage();
	int getQuantity();
	std::string getInfo();
private:
	//动态信息
	int usage;
	int totalGPUMemory;
	int usingGPUMemory;
	int memoryUsage;
	//静态信息
	int quantity;
	std::string info;
};
#endif