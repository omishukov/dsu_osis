#include <QMutexLocker>
#include "obslink.h"

ObsLink::ObsLink(const QString &connectionGroupName, Configuration &configFile, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
   , ui_If(0)
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

void ObsLink::threadStarted()
{

}

void ObsLink::threadFinished()
{

}
