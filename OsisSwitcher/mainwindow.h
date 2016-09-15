#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMetaEnum>
#include <QValidator>
#include <QMap>
#include <QStandardItemModel>
#include "isucalclink.h"
#include "osis/dataparser.h"
#include "obs/actions.h"
#include "obs/obsaction.h"
#include "obs/scenetableui.h"
#include "obs/sceneswitcher.h"
#include "actiontoscene.h"

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

   void UpdateSceneConfiguration();

private slots:
   void on_Connect_PB_clicked();
   void IsuCalcConnected();
   void IsuCalcReconnecting();
   void IsuCalcDisconnected();

   void on_Reconnect_CB_stateChanged(int);

signals:
   void ChangedIsuCalcSettings(const QString&, quint16, uint);
   void EstablishConnection();
   void StopConnection();

private:
   void InitIsuCalcLink();
   void InitOsisParser();
   void InitObsData();
   void InitSceneSwitcher();
   void SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled);
   void ReadSettings();
   void setIpValitation();
   void SaveSettings();
   QString GetObsSceneFile();
   void InitActionSceneUi();

   Ui::MainWindow *ui;
   DataQueue DataIf;
   IsuCalcLink CalcLink;
   QThread CalcLinkThread;
   QMetaEnum MetaCalLinkEnum;
   QValidator* CalcIpValidator;
   QValidator* PortValidator;
   OsisParser OsisDataParser;
   QThread OsisDataParserThread;
   Actions ObsDataSaver;
   QThread ObsDataSaverThread;
   QString OBS_Path;
   SceneTableUi TableGui;
   QStandardItemModel* TableModel;
   ObsSceneSwitcher Switcher;
   QThread SwitcherThread;
   ActionToScene Action2Scene;

};

#endif // MAINWINDOW_H
