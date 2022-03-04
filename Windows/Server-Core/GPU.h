#ifndef GPU_HSharedSystemMemory
#define GPU_H
class GPU
{
public:
	GPU();
	~GPU();

	void updateBasicInfo();

	int getQuantity();
	std::string getInfo(int n);
	int getDedicatedVideoMemory(int n);
	//int getDedicatedSystemMemory(int n);
	int getSharedSystemMemory(int n);
private:
	int quantity;
	int* dedicatedVideoMemory; //The number of bytes of dedicated video memory that are not shared with the CPU.
	//int* dedicatedSystemMemory; //The number of bytes of dedicated system memory that are not shared with the CPU. This memory is allocated from available system memory at boot time.
	int* sharedSystemMemory; //The number of bytes of shared system memory. This is the maximum value of system memory that may be consumed by the adapter during operation. Any incidental memory consumed by the driver as it manages and uses video memory is additional.
	std::string* info;
};
#endif