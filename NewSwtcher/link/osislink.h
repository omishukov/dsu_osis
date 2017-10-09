#ifndef OSISLINK_H
#define OSISLINK_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include "link/linkif.h"
#include "ui/uilinkif.h"
#include <configuration.h>

class OsisLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit OsisLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

   void Start();
   void Stop();

   void SetUiIf(UiLinkIf* uiIf) { ui_If = uiIf; }

signals:

public slots:
   void threadStarted();
   void threadFinished();

private:
   QThread osisLinkThread;
   QTcpSocket* qtcp_Socket;
   UiLinkIf* ui_If;
};

#endif // OSISLINK_H
