#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QThread>
#include <QMetaEnum>
#include "isucalclink.h"
#include "dataqueue.h"

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

public slots:
   void IsuCalcConnected();
   void IsuCalcReconnecting();
   void IsuCalcDisconnected();

signals:
   void ChangedIsuCalcSettings(const QString&, quint16, uint);
   void EstablishConnection();
   void StopConnection();

private:
    Ui::MainWindow *ui;

    void InitIsuCalcLink();
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

};

#endif // MAINWINDOW_H
