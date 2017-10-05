#include "configuration.h"

Configuration::Configuration(QString &fileName)
   : qset_ConfigFile(fileName, QSettings::IniFormat)
{
}

bool Configuration::GetIpInfo(const QString &group, QString &ipAddr, QString &ipPort)
{
   qset_ConfigFile.beginGroup(group);
   QVariant IpAddr = qset_ConfigFile.value("ADDR");
   QVariant IpPort = qset_ConfigFile.value("PORT");
   qset_ConfigFile.endGroup();

   if (IpAddr.isNull() || IpPort.isNull())
   {
      return false;
   }
   ipAddr = IpAddr.toString();
   ipPort = IpPort.toString();
   return true;
}
