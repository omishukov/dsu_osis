#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calcconnectionthread.h"

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_ClientServerCB_activated(int index);
   void on_ConnectButton_clicked();

   void showConnecting();

private:
   void loadConnectionSettings();
   void setIpValitation();
   void readSettings();
   void writeSettings();

private:
   Ui::MainWindow *ui;

   typedef enum
   {
      CLIENT,
      SERVER
   } ConnectAs;

   typedef enum
   {
      DISCONNECTED,
      CONNECTING,
      CONNECTED
   } ConnectState;

   ConnectAs ConnectionType;
   QString IpAddress;
   QString IpPort;
   ConnectState ConnectionStatus;
   CalcConnectionThread OsisLink;
};

#endif // MAINWINDOW_H
