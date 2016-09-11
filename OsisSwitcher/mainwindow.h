#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMetaEnum>
#include <QValidator>
#include "isucalclink.h"
#include "osis/dataparser.h"

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
   void SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled);
   void ReadSettings();
   void setIpValitation();
   void SaveSettings();


   Ui::MainWindow *ui;
   DataQueue DataIf;
   IsuCalcLink CalcLink;
   QThread CalcLinkThread;
   QMetaEnum MetaCalLinkEnum;
   QValidator* CalcIpValidator;
   QValidator* PortValidator;
   OsisParser OsisDataParser;
   QThread OsisDataParserThread;

};

#endif // MAINWINDOW_H
