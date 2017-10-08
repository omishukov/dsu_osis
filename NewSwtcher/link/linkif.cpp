#include "linkif.h"

LinkIf::LinkIf(const QString &grpName, Configuration &cfgFile)
   : groupName(grpName)
   , configFile(cfgFile)
{
}

void LinkIf::GetIpInfo(QString &ipAddr, QString &ipPort)
{
   QString IpAddress, IpPort;
   if (configFile.GetIpInfo(groupName, IpAddress, IpPort) == false)
   {
      IpAddress = "127.0.0.1";
      IpPort = "4000";
   }
   ipAddr = IpAddress;
   ipPort = IpPort;
}

void LinkIf::SaveIpInfo(QString &ipAddr, QString &ipPort)
{
   configFile.SaveIpInfo(groupName, ipAddr, ipPort);
}
