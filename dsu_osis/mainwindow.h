#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "calcconnectionthread.h"


namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QString logName, QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_ClientServerCB_activated(int index);
   void on_ConnectButton_clicked();

   void showConnectionState();

   void on_IPv4Address_editingFinished();

   void on_IPv4Port_editingFinished();

   void on_LogDataCB_stateChanged(int arg1);

   void on_LogErrorCB_stateChanged(int arg1);

   void on_LogWarningCB_stateChanged(int arg1);

   void on_LogDebugCB_stateChanged(int arg1);

   void on_ChangeObsConfigPathPB_clicked();

private:
   void loadSettings();
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

   ConnectAs ConnectionType;
   QString IpAddress;
   QString IpPort;
   CalcConnectionThread OsisLink;
   class IsuCompetition* Competition;
   QThread *SceneSwitcherThread;
   class ObsSceneSwitcher *SceneSwitcher;
   QString OBS_Path;
};

#endif // MAINWINDOW_H
