#include "obslink.h"

ObsLink::ObsLink(const QString &connectionGroupName, Configuration &configFile, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
{

}

void ObsLink::Connect()
{

}

void ObsLink::Disconnect()
{

}
