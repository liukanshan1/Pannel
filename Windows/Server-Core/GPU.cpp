#include "libCommon.h"
#include "GPU.h"
GPU::GPU()
{
    createLogs('i', "初始化GPU基本信息");
	quantity = -1;
    dedicatedVideoMemory = nullptr;
    //dedicatedSystemMemory = nullptr;
    sharedSystemMemory = nullptr;
    info = nullptr;
    updateBasicInfo();
}
GPU::~GPU()
{
    if (dedicatedVideoMemory != nullptr)
    {
        delete[] dedicatedVideoMemory;
    }
    /*if (dedicatedSystemMemory != nullptr)
    {
        delete[] dedicatedSystemMemory;
    }*/
    if (sharedSystemMemory != nullptr)
    {
        delete[] sharedSystemMemory;
    }
    if (info != nullptr)
    {
        delete[] info;
    }
}

void GPU::updateBasicInfo()
{
    quantity = 0;
    IDXGIFactory* pFactory;
    IDXGIAdapter* pAdapter;
    std::vector <IDXGIAdapter*> gpu; //显卡
    //创建一个DXGI工厂
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
    if (FAILED(hr))
    {
        throwError('g', 1, "获取显卡信息失败.");
        return;
    }
    //获取GPU数量并开辟内存
    createLogs('i', "获取GPU数量");
    while (pFactory->EnumAdapters(quantity, &pAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        gpu.push_back(pAdapter);
        quantity++;
    }
    dedicatedVideoMemory = new int[quantity];
    //dedicatedSystemMemory = new int[quantity];
    sharedSystemMemory = new int[quantity];
    info = new std::string[quantity];
    //分别获取详细信息
    createLogs('i', "获取GPU信息、GPU内存");
    for (size_t i = 0; i < gpu.size(); i++)
    {
        DXGI_ADAPTER_DESC adapterDesc;
        gpu[i]->GetDesc(&adapterDesc);
        std::wstring temp(adapterDesc.Description);
        info[i] = WStringToString(temp);
        //dedicatedSystemMemory[i] = adapterDesc.DedicatedSystemMemory / 1024 / 1024;
        dedicatedVideoMemory[i] = adapterDesc.DedicatedVideoMemory / 1024 / 1024; //GPU内存
        sharedSystemMemory[i] = adapterDesc.SharedSystemMemory / 1024 / 1024; //共享GPU内存
    }
    gpu.clear();
}

int GPU::getQuantity()
{
	return quantity;
}
int GPU::getDedicatedVideoMemory(int n)
{
	return dedicatedVideoMemory[n];
}
//int GPU::getDedicatedSystemMemory(int n)
//{
//	return dedicatedSystemMemory[n];
//}
int GPU::getSharedSystemMemory(int n)
{
	return sharedSystemMemory[n];
}
std::string GPU::getInfo(int n)
{
	return info[n];
}
