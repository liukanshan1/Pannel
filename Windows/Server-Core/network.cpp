#include "libCommon.h"
#include "network.h"
network::network()
{
    quantity = 0;
    bestIndex = -1;
    index = nullptr;
    description = nullptr;
    hardwareAddress = nullptr;
    IPv4 = nullptr;
    IPv6 = nullptr;
    name = nullptr;
    upload = nullptr;
    download = nullptr;
    status = nullptr;
    //��ȡ��������
    PIP_ADAPTER_ADDRESSES pAdapter = nullptr;
    PIP_ADAPTER_ADDRESSES currentAdapter = nullptr;
    ULONG bufferSize = 0;
    GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAdapter, &bufferSize);
    pAdapter = (IP_ADAPTER_ADDRESSES*)malloc(bufferSize);
    if ((GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST, NULL, pAdapter, &bufferSize)) == NO_ERROR)
    {
        currentAdapter = pAdapter;
        while (currentAdapter)
        {
            quantity++;
            currentAdapter = currentAdapter->Next;
        }
    }
    else
    {
        return;
    }
    //�����ڴ�
    index = new int[quantity];
    description = new std::string[quantity];
    hardwareAddress = new std::string[quantity];
    IPv4 = new std::string[quantity];
    IPv6 = new std::string[quantity];
    upload = new io[quantity];
    download = new io[quantity];
    status = new bool[quantity];
    name = new std::string[quantity];
    //Ѱ���������
    IPAddr ipAddress = { 0 };
    if (NO_ERROR != GetBestInterface(ipAddress, &bestIndex))
    {
        return;
    }
    //������þ�̬��Ϣ
    currentAdapter = pAdapter;
    for (int i = 0; i < quantity; i++)
    {
        //��ȡmac��ַ
        char temp[100];
        sprintf_s(temp, "%.2x-%.2x-%.2x-%.2x-%.2x-%.2x",
            currentAdapter->PhysicalAddress[0], currentAdapter->PhysicalAddress[1],
            currentAdapter->PhysicalAddress[2], currentAdapter->PhysicalAddress[3],
            currentAdapter->PhysicalAddress[4], currentAdapter->PhysicalAddress[5]);
        hardwareAddress[i] += temp;
        //��ȡname
        name[i] = tcharToString(currentAdapter->FriendlyName);
        //��ȡstatus
        status[i] = (currentAdapter->OperStatus == IfOperStatusUp ? true : false);
        //��ȡindex
        index[i] = currentAdapter->IfIndex;
        //��ȡdescription
        description[i] = WStringToString(currentAdapter->Description);
        //��ȡIPv4��IPv6��ַ
        PIP_ADAPTER_UNICAST_ADDRESS pAddress = currentAdapter->FirstUnicastAddress;
        while(pAddress != NULL)
        {
            char temp[100];
            DWORD tempLength = 100;
            if (pAddress->Address.lpSockaddr->sa_family == AF_INET)
            {
                sockaddr_in* ipv4 = (sockaddr_in*)pAddress->Address.lpSockaddr;
                IPv4[i] = inet_ntop(AF_INET, &(ipv4->sin_addr), temp, tempLength);
            }
            else if (pAddress->Address.lpSockaddr->sa_family == AF_INET6)
            {
                sockaddr_in6* ipv6 = (sockaddr_in6*)pAddress->Address.lpSockaddr;
                IPv6[i] = inet_ntop(AF_INET6, &(ipv6->sin6_addr), temp, tempLength);
            }
            pAddress = pAddress->Next;
        }
        currentAdapter = currentAdapter->Next;
    }
    free(pAdapter);
    //��ȡ�ϴ������ٶ�
    updateNetworkUD(this);
}
network::~network()
{
	//�ͷ��ڴ�
    if (description != nullptr)
    {
        delete[] description;
    }
    if (hardwareAddress != nullptr)
    {
        delete[] hardwareAddress;
    }
    if (IPv4 != nullptr)
    {
        delete[] IPv4;
    }
    if (IPv6 != nullptr)
    {
        delete[] IPv6;
    }
    if (upload != nullptr)
    {
        delete[] upload;
    }
    if (download != nullptr)
    {
        delete[]  download;
    }
    if (index != nullptr)
    {
        delete[]  index;
    }
    if (status != nullptr)
    {
        delete[]  status;
    }
    if (name != nullptr)
    {
        delete[]  name;
    }
}

int network::getQuantity()
{
	return quantity;
}
DWORD network::getBestIndex()
{
    return bestIndex;
}
std::string network::getDescription(int n)
{
    return description[n];
}
std::string network::getHardwareAddress(int n)
{
    return hardwareAddress[n];
}
std::string network::getIPv4(int n)
{
	return IPv4[n];
}
std::string network::getIPv6(int n)
{
	return IPv6[n];
}
io network::getUpload(int n)
{
	return upload[n];
}
io network::getDownload(int n)
{
	return download[n];
}
bool network::getStatus(int n)
{
    return status[n];
}
std::string network::getName(int n)
{
    return name[n];
}