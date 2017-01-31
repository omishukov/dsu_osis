#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QThread>
#include <QMetaEnum>
#include <QLabel>
#include "isucalclink.h"
#include "dataqueue.h"
#include "websocketserver.h"
#include "proxyserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   enum IsuCalcLinkButton
   {
      Connect,
      Cancel,
      Disconnect
   };
   Q_ENUM(IsuCalcLinkButton)

private slots:
   void on_Connect_PB_clicked();
   void on_Reconnect_CB_stateChanged(int);

   void on_ProxyServerPort_LE_editingFinished();

   void on_IsuCalcIP_LE_editingFinished();

public slots:
   void IsuCalcConnected();
   void IsuCalcReconnecting();
   void IsuCalcDisconnected();
   void NewConnection(QString& addr);
   void ClientDisconnected(QString& addr);

signals:
   void ChangedIsuCalcSettings(const QString&, quint16, uint);
   void ChangedProxyServerSettings(quint16);
   void DisconnectAllClients();
   void EstablishConnection();
   void StopConnection();

private:
   Ui::MainWindow *ui;

   void InitIsuCalcFsLink();
   void InitWebsocketServer();
   void InitProxyServer();
   void setIpValitation();
   void ReadSettings();
   void saveSettings();
   void SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled);


   QList<QLabel*> ConnStatusUIList;
   QValidator* CalcIpValidator;
   QValidator* PortValidator;
   IsuCalcLink CalcLink;
   QMetaEnum MetaCalLinkEnum;
   DataQueue DataIf;
   OsisWebsocketServer WebsockServer;
   ProxyServer Server;
   QThread ProxyServerThread;

};

#endif // MAINWINDOW_H
