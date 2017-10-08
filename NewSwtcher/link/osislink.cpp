#include "link/osislink.h"

OsisLink::OsisLink(const QString &connectionGroupName, Configuration& configFile, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
{
   moveToThread(&osisLinkThread);
   connect(&osisLinkThread, SIGNAL(started()), this, SLOT(thread_started())); // on thread start
   connect(&osisLinkThread, SIGNAL(finished()), this, SLOT(thread_finished())); // on thread stop
}

void OsisLink::Connect()
{

}

void OsisLink::Disconnect()
{

}

void OsisLink::threadStarted()
{

}

void OsisLink::threadFinished()
{

}
