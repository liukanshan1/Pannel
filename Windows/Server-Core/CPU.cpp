#include "libCommon.h"
#include "CPU.h"
CPU::CPU()
{
    updateBasicInfo();
    update();
}
void CPU::updateBasicInfo()
{
    ////��ȡ�߼�����������
    //SYSTEM_INFO coreInfo;
    //GetSystemInfo(&coreInfo);
    //cpuInfo.logicalProcessorQuantity = coreInfo.dwNumberOfProcessors;

    //��ȡCPU��Ϣ
    updateLogicalProcessorInfo();
    //��ȡCPU����
    updateCpuDiscription();
    //��ȡCPU�ܹ�
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
void CPU::update()
{
    updateCpuUsage();
}

void CPU::updateCpuUsage()
{
    //const wchar_t* fileName = L"CpuUsage.bat";
    //const char* fileName = "CpuUsage";
    runTask(L"CpuUsage.bat");
    openFile("CpuUsage", usage);
}
void CPU::updateCpuDiscription()
{

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
DWORD CountSetBits(ULONG_PTR bitMask)
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
        /*_tprintf(TEXT("\nGetLogicalProcessorInformation is not supported.\n"));*/
        return /*(1)*/;
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
                   /* _tprintf(TEXT("\nError: Allocation failure\n"));*/
                    return /*(2)*/;
                }
            }
            else
            {
                /*_tprintf(TEXT("\nError %d\n"), GetLastError());*/
                return /*(3)*/;
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
            _tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
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
    return /*0*/;
}
//https://docs.microsoft.com/zh-cn/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlogicalprocessorinformation?redirectedfrom=MSDN

   
