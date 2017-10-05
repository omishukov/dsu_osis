#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>

class Configuration
{
public:
   Configuration(QString &fileName);

   bool GetIpInfo(const QString& group, QString& ipAddr, QString& ipPort);

private:
   QSettings qset_ConfigFile;
};

#endif // CONFIGURATION_H
