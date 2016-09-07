#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QThread>
#include <QMetaEnum>
#include "isucalclink.h"

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

public slots:
   void IsuCalcConnected();

signals:
   void ChangedIsuCalcSettings(const QString&, quint16, uint);
   void EstablishConnection();

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
    IsuCalcLinkThread CalcLink;
    QMetaEnum MetaCalLinkEnum;

};

#endif // MAINWINDOW_H
