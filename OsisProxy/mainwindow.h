#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QThread>
#include <QMetaEnum>
#include "isucalclink.h"
#include "dataqueue.h"
#include "osisdataproxy.h"
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

public slots:
   void IsuCalcConnected();
   void IsuCalcReconnecting();
   void IsuCalcDisconnected();
   void NewConnection(quint32 addr);
   void ClientDisconnected(quint32 addr);

signals:
   void ChangedIsuCalcSettings(const QString&, quint16, uint);
   void ChangedProxyServerSettings(quint16);
   void EstablishConnection();
   void StopConnection();

private:
   Ui::MainWindow *ui;

   void InitIsuCalcLink();
   void InitOsisDataProxy();
   void InitProxyServer();
   void setIpValitation();
   void ReadSettings();
   void saveSettings();
   void SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled);


   QValidator* CalcIpValidator;
   QValidator* PortValidator;
   QThread CalcLinkThread;
   IsuCalcLink CalcLink;
   QMetaEnum MetaCalLinkEnum;
   DataQueue DataIf;
   OsisDataProxy DataProxy;
   QThread DataProxyThread;
   ProxyServer Server;
   QThread ProxyServerThread;

};

#endif // MAINWINDOW_H
