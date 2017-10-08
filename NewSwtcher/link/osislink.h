#ifndef OSISLINK_H
#define OSISLINK_H

#include <QObject>
#include <QThread>
#include "link/linkif.h"
#include <configuration.h>

class OsisLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit OsisLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

signals:

public slots:
   void threadStarted();
   void threadFinished();

private:
   QThread osisLinkThread;
};

#endif // OSISLINK_H
