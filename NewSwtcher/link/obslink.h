#ifndef OBSLINK_H
#define OBSLINK_H

#include <QObject>
#include "linkif.h"
#include <configuration.h>

class ObsLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit ObsLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

signals:

public slots:
};

#endif // OBSLINK_H
