#ifndef GPU_H
#define GPU_H
class GPU //�����GPU��ʵ��
{
public:
	GPU();
	~GPU();
	//������Ϣ
	void updateBasicInfo();
	void update();
	//������Ϣ
	int getUsage();
	int getTotalGPUMemory();
	int getUsingGPUMemory();
	int getMemoryUsage();
	int getQuantity();
	std::string getInfo();
private:
	//��̬��Ϣ
	int usage;
	int totalGPUMemory;
	int usingGPUMemory;
	int memoryUsage;
	//��̬��Ϣ
	int quantity;
	std::string info;
};
#endif