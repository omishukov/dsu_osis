#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMetaEnum>
#include <QValidator>
#include <QMap>
#include "isucalclink.h"
#include "osis/dataparser.h"
#include "obs/actions.h"
#include "obs/obsaction.h"
#include "obs/scenetableui.h"
#include "obs/sceneswitcher.h"
#include "obs/obsscenes.h"
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

   void on_ChangeObsConfigPathPB_clicked();

   void on_TransitionCB_currentIndexChanged(const QString &arg1);

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
   OsisParser OsisDataParser;
   QThread OsisDataParserThread;
//   Actions ObsDataSaver;
//   QThread ObsDataSaverThread;
   QString OBS_Path;
   SceneTableUi* TableGui;
   ObsSceneSwitcher Switcher;
   QThread SwitcherThread;
   ActionToScene Action2Scene;
   ObsScenes Obs;
   QString CurrentTransition;

};

#endif // MAINWINDOW_H
