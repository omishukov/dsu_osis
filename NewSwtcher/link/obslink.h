#ifndef OBSLINK_H
#define OBSLINK_H

#include <QObject>
#include <QWebSocket>
#include <link/linkif.h>
#include <ui/uilinkif.h>
#include <configuration.h>

class ObsLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit ObsLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

   void Start();
   void Stop();

   void SetUiIf(UiLinkIf* uiIf) { ui_If = uiIf; }

signals:

public slots:

private:
   UiLinkIf* ui_If;
   QWebSocket obsWebSocketClient;

};

#endif // OBSLINK_H
