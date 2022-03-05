#include "libCommon.h"
#include "network.h"
network::network()
{
    quantity = 0;
    bestIndex = -1;
    description = nullptr;
    hardwareAddress = nullptr;
    IPv4 = nullptr;
    IPv6 = nullptr;
    gatewayAddress = nullptr;
    dhcp = nullptr;
    upload = nullptr;
    download = nullptr;
    //获取网卡数量
    ULONG bufferSize = 0;
    IP_ADAPTER_INFO* pAdapter = nullptr;
    if (GetAdaptersInfo(pAdapter, &bufferSize) == ERROR_BUFFER_OVERFLOW)
    {
        pAdapter = (IP_ADAPTER_INFO*)new char[bufferSize];
    }
    else
    {
        return;
    }
    if (GetAdaptersInfo(pAdapter, &bufferSize) != ERROR_SUCCESS)
    {
        return;
    }
    for (auto* currentAdapter = pAdapter; currentAdapter != NULL; currentAdapter = currentAdapter->Next) 
    {
        quantity++;
    }
    //开辟内存
    description = new std::string[quantity];
    hardwareAddress = new std::string[quantity];
    IPv4 = new std::string[quantity];
    IPv6 = new std::string[quantity];
    gatewayAddress = new std::string[quantity];
    dhcp = new dhcpInfo[quantity];
    upload = new io[quantity];
    download = new io[quantity];
    //寻找最佳网卡
    IPAddr ipAddress = { 0 };
    if (NO_ERROR != GetBestInterface(ipAddress, &bestIndex))
    {
        return;
    }
    //遍历获得description、IPv4、gatewayAddress、dhcp
    for (int i = 0; i < quantity; i++)
    {
        auto* currentAdapter = pAdapter;
        description[i] = currentAdapter->Description;
        IPv4[i] = currentAdapter->IpAddressList.IpAddress.String;
        gatewayAddress[i] = currentAdapter->GatewayList.IpAddress.String;
        if (currentAdapter->DhcpEnabled!=0)
        {
            dhcp[i].enable = true;
            dhcp[i].dhcpAddress = currentAdapter->DhcpServer.IpAddress.String;
            dhcp[i].LeaseExpires= currentAdapter->LeaseExpires;
            dhcp[i].LeaseObtained = currentAdapter->LeaseObtained;
        }
        currentAdapter = currentAdapter->Next;
    }
    delete[] pAdapter;
    //获取MAC地址，IPv6
	updateBasicInfo();
    //获取上传下载速度
    updateNetworkUD(this);
}
void network::updateBasicInfo()
{
    //获取MAC地址，IPv6




}
network::~network()
{
	//释放内存
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
    if (gatewayAddress != nullptr)
    {
        delete[] gatewayAddress;
    }
    if (dhcp != nullptr)
    {
        delete[] dhcp;
    }
    if (upload != nullptr)
    {
        delete[] upload;
    }
    if (download != nullptr)
    {
        delete[]  download;
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
std::string network::getGatewayAddress(int n)
{
    return gatewayAddress[n];
}
dhcpInfo network::getDHCP(int n)
{
    return dhcp[n];
}
io network::getUpload(int n)
{
	return upload[n];
}
io network::getDownload(int n)
{
	return download[n];
}