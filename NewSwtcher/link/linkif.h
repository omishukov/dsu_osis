#ifndef LINKIF_H
#define LINKIF_H

#include <QString>
#include <configuration.h>

class LinkIf
{
public:
   LinkIf(const QString& grpName, Configuration& cfgFile);

   virtual void Connect() = 0;
   virtual void Disconnect() = 0;
   QString GetGroupName() { return groupName; };
   void GetIpInfo(QString& ipAddr, QString& ipPort);
   void SaveIpInfo(QString& ipAddr, QString& ipPort);

private:
   const QString& groupName;
   Configuration& configFile;
};

#endif // LINKIF_H
