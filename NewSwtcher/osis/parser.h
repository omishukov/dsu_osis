#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QThread>
#include <osis/dataqueue.h>

class OsisParser : public QObject
{
   Q_OBJECT
public:
   explicit OsisParser(DataQueue* data, QObject *parent = nullptr);

   void Start();
   void Stop();

signals:
   void SignalThrTerminateRequest();

public slots:
   void ReceiveData();
   void SlotThrTerminateRequest();
   void SlotThrStarted();
   void SlotThrFinished();

private:
   void ParseXml(QByteArray* OsisXml);

private:
   QThread ParserThread;
   DataQueue* OsisRawData;
};

#endif // PARSER_H
