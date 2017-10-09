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

void ObsLink::Start()
{

}

void ObsLink::Stop()
{

}
