#include <QDebug>
#include "parser.h"

OsisParser::OsisParser(DataQueue *data, QObject *parent)
   : QObject(parent)
   , OsisRawData(data)
{
   moveToThread(&ParserThread);
   connect(&ParserThread, SIGNAL(started()), this, SLOT(SlotThrStarted()), Qt::QueuedConnection); // on thread start
   connect(&ParserThread, SIGNAL(finished()), this, SLOT(SlotThrFinished()), Qt::QueuedConnection); // on thread stop
}

void OsisParser::Start()
{
   ParserThread.start();
}

void OsisParser::Stop()
{
   emit SignalThrTerminateRequest();
   ParserThread.wait();
}

void OsisParser::ReceiveData()
{
   QByteArray* OsisXml = 0;
   while(OsisRawData->GetData(OsisXml))
   {
      if (OsisXml)
      {
         ParseXml(OsisXml);
         delete OsisXml;
         OsisXml = 0;
      }
   }
}

void OsisParser::SlotThrTerminateRequest()
{
   qInfo() << "OsisParser thread termination request";
   ParserThread.quit();
}

void OsisParser::SlotThrStarted()
{
   qInfo() << "OsisParser thread started";
   connect(this, SIGNAL(SignalThrTerminateRequest()), this, SLOT(SlotThrTerminateRequest()), Qt::QueuedConnection);
   connect(OsisRawData, SIGNAL(NewData()), this, SLOT(ReceiveData()), Qt::QueuedConnection); // Update UI
}

void OsisParser::SlotThrFinished()
{
   qInfo() << "OsisParser thread stopped";
}

void OsisParser::ParseXml(QByteArray* OsisXml)
{
}

