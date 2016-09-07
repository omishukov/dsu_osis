#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

QString inifile = "osisproxy.ini";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , CalcIpValidator(0)
    , PortValidator(0)
    , MetaCalLinkEnum(QMetaEnum::fromType<IsuCalcLinkButton>())
{
   ui->setupUi(this);
   InitIsuCalcLink();
   ReadSettings();
}

MainWindow::~MainWindow()
{
   CalcLinkThread.quit();
   CalcLinkThread.wait();
   saveSettings();

   delete ui;
   delete CalcIpValidator;
   delete PortValidator;
}

void MainWindow::InitIsuCalcLink()
{
   CalcLink.moveToThread(&CalcLinkThread);
   connect(this, SIGNAL(EstablishConnection()), &CalcLink, SLOT(Establish())); // Connect to the IsuCalc
   connect(&CalcLink, SIGNAL(Established()), this, SLOT(IsuCalcConnected())); // Connect to the IsuCalc
   connect(this, SIGNAL(ChangedIsuCalcSettings(const QString&, quint16, uint)),
           &CalcLink, SLOT(ChangedSettings(const QString&, quint16, uint))); // on settings change
   connect(&CalcLinkThread, SIGNAL(started()), &CalcLink, SLOT(Initialize())); // on thread start
   connect(&CalcLinkThread, SIGNAL(finished()), &CalcLink, SLOT(Uninit())); // on thread stop
   CalcLinkThread.start();
}

void MainWindow::setIpValitation()
{
   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   CalcIpValidator = new QRegExpValidator(ipRegex, this);
   ui->IsuCalcIP_LE->setValidator(CalcIpValidator);

   PortValidator = new QIntValidator(6,65535,this);// 0 to 65535
   ui->IsuCalcPort_LE->setValidator(PortValidator);//ports
   ui->ProxyServerPort_LE->setValidator(PortValidator);//ports
}

void MainWindow::ReadSettings()
{
   setIpValitation();
   QSettings settings(inifile, QSettings::IniFormat);

   settings.beginGroup("Connection");
   ui->IsuCalcIP_LE->setText(settings.value("isu_calc_ip", "127.0.0.1").toString());
   ui->IsuCalcPort_LE->setText(settings.value("isu_calc_port", "4000").toString());
   ui->Reconnect_CB->setCheckState(settings.value("isu_calc_recon", false).toBool()?Qt::Checked:Qt::Unchecked);
   ui->ProxyServerPort_LE->setText(settings.value("proxy_server_port", "5000").toString());

   ui->Connect_PB->setText(MetaCalLinkEnum.valueToKey(Connect));

   emit ChangedIsuCalcSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUShort(),ui->Reconnect_CB->checkState());
//    emit ChangedProxyServerSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUInt(),(uint)ui->Reconnect_CB->checkState());
   settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings(inifile, QSettings::IniFormat);

    settings.beginGroup("Connection");
    settings.setValue("isu_calc_ip", ui->IsuCalcIP_LE->text());
    settings.setValue("isu_calc_port", ui->IsuCalcPort_LE->text());
    settings.setValue("isu_calc_recon", ui->Reconnect_CB->checkState());
    settings.setValue("proxy_server_port", ui->ProxyServerPort_LE->text());
    settings.endGroup();

}

void MainWindow::on_Connect_PB_clicked()
{
   switch(MetaCalLinkEnum.keyToValue(ui->Connect_PB->text().toLocal8Bit().constData()))
   {
      case Connect:
      {
         SetLinkStatus("Connecting...", MetaCalLinkEnum.valueToKey(Cancel), true, false, false);
         emit EstablishConnection();
      }
         break;
      case Cancel:
      {

      }
         break;
      case Disconnect:
      {

      }
         break;

   }
}

void MainWindow::IsuCalcConnected()
{
    SetLinkStatus("Connected", MetaCalLinkEnum.valueToKey(Disconnect), true, false, false);
}

void MainWindow::SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled)
{
   ui->IsuCalcLinkStatus->setText(label);
   ui->Connect_PB->setText(buttonText);
   ui->Connect_PB->setEnabled(buttonEnabled);
   ui->IsuCalcIP_LE->setEnabled(ipAddrEnabled);
   ui->IsuCalcPort_LE->setEnabled(ipPortEnabled);
}
