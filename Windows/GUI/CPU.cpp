#include "libCommon.h"
#include "CPU.h"
CPU::CPU()
{
    createLogs('i', "初始化CPU基本信息");
    usage = -1;
    info.numaNodeQuantity = -1;
    info.processorPackageQuantity = -1;
    info.processorCoreQuantity = -1;
    info.logicalProcessorQuantity = -1;
    info.processorL1CacheQuantity = -1;
    info.processorL2CacheQuantity = -1;
    info.processorL3CacheQuantity = -1;
    updateBasicInfo();
    createLogs('i', "获取CPU使用率");
    updateCpuUsage(this);
}

void CPU::updateBasicInfo()
{
    ////获取逻辑处理器数量
    //SYSTEM_INFO coreInfo;
    //GetSystemInfo(&coreInfo);
    //cpuInfo.logicalProcessorQuantity = coreInfo.dwNumberOfProcessors;

    //获取CPU信息
    createLogs('i', "获取CPU详细信息");
    updateLogicalProcessorInfo();
    //获取CPU描述
    createLogs('i', "获取CPU描述");
    updateCpuDiscription();
    //获取CPU架构
    createLogs('i', "获取CPU架构");
    SYSTEM_INFO architectureInfo;
    GetSystemInfo(&architectureInfo);
    switch (architectureInfo.wProcessorArchitecture)
    {
    case 9:
        info.architecture = "x64";
        break;
    case 5:
        info.architecture = "ARM";
        break;
    case 12:
        info.architecture = "ARM64";
        break;
    case 6:
        info.architecture = "Intel Itanium-based";
        break;
    case 0:
        info.architecture = "x86";
        break;
    default:
        info.architecture = "Unknown";
        break;
    }
}
void CPU::updateCpuDiscription()
{
    runTask(L"CpuDiscription.bat");
    openCpuDiscription("CpuDiscription", info.discription);
}

std::string CPU::getDescription()
{
    if (int(info.discription[0])==0)
    {
        info.discription.erase(0, 1);
    }
    return info.discription;
}
cpuInfo CPU::getInfo()
{
    return info;
}
int CPU::getUsage()
{
    return usage;
}

// Helper function to count set bits in the processor mask.
DWORD CPU::CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}
void CPU::updateLogicalProcessorInfo()
{
    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),
        "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
        throwError('c',1,"GetLogicalProcessorInformation is not supported.");
        return;
    }

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                    returnLength);

                if (NULL == buffer)
                {
                    throwError('c',2,"Allocation failure.");
                    return;
                }
            }
            else
            {
                throwError('c', 3,"未知错误，调用Getlasterror()获得错误代码.");
                return;
            }
        }
        else
        {
            done = TRUE;
        }
    }

    ptr = buffer;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
        case RelationNumaNode:
            // Non-NUMA systems report a single record of this type.
            numaNodeCount++;
            break;

        case RelationProcessorCore:
            processorCoreCount++;

            // A hyperthreaded core supplies more than one logical processor.
            logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
            Cache = &ptr->Cache;
            if (Cache->Level == 1)
            {
                processorL1CacheCount++;
            }
            else if (Cache->Level == 2)
            {
                processorL2CacheCount++;
            }
            else if (Cache->Level == 3)
            {
                processorL3CacheCount++;
            }
            break;

        case RelationProcessorPackage:
            // Logical processors share a physical package.
            processorPackageCount++;
            break;

        default:
            throwError('c', 4, "Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.");
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

    info.numaNodeQuantity = numaNodeCount;
    info.processorCoreQuantity = processorCoreCount;
    info.logicalProcessorQuantity = logicalProcessorCount;
    info.processorPackageQuantity = processorPackageCount;
    info.processorL1CacheQuantity = processorL1CacheCount;
    info.processorL2CacheQuantity = processorL2CacheCount;
    info.processorL3CacheQuantity = processorL3CacheCount;

    free(buffer);
    return;
}
//https://docs.microsoft.com/zh-cn/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlogicalprocessorinformation?redirectedfrom=MSDN

   
