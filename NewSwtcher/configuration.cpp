#include "configuration.h"

const QString ADDR_KEY = "ADDR";
const QString PORT_KEY = "PORT";

Configuration::Configuration(QString &fileName)
   : qset_ConfigFile(fileName, QSettings::IniFormat)
{
}

bool Configuration::GetIpInfo(const QString &group, QString &ipAddr, QString &ipPort)
{
   qset_ConfigFile.beginGroup(group);
   QVariant IpAddr = qset_ConfigFile.value(ADDR_KEY);
   QVariant IpPort = qset_ConfigFile.value(PORT_KEY);
   qset_ConfigFile.endGroup();

   if (IpAddr.isNull() || IpPort.isNull())
   {
      return false;
   }
   ipAddr = IpAddr.toString();
   ipPort = IpPort.toString();
   return true;
}

void Configuration::SaveIpInfo(const QString &group, const QString &ipAddr, const QString &ipPort)
{
   qset_ConfigFile.beginGroup(group);
   qset_ConfigFile.setValue(ADDR_KEY, ipAddr);
   qset_ConfigFile.setValue(PORT_KEY, ipPort);
   qset_ConfigFile.endGroup();
}
