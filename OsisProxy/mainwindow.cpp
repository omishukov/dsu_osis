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
   InitOsisDataProxy();
   InitProxyServer();
   ReadSettings();
}

MainWindow::~MainWindow()
{
   CalcLinkThread.quit();
   CalcLinkThread.wait();
   DataProxyThread.quit();
   DataProxyThread.wait();
   ProxyServerThread.quit();
   ProxyServerThread.wait();
   saveSettings();

   delete CalcIpValidator;
   delete PortValidator;
   delete ui;
}

void MainWindow::InitIsuCalcLink()
{
   CalcLink.SetDataIf(&DataIf);
   CalcLink.moveToThread(&CalcLinkThread);

   connect(this, SIGNAL(EstablishConnection()), &CalcLink, SLOT(Establish())); // Connect to the IsuCalc
   connect(this, SIGNAL(StopConnection()), &CalcLink, SLOT(StopConnection())); // Disconnect from the IsuCalc
   connect(&CalcLink, SIGNAL(Established()), this, SLOT(IsuCalcConnected())); // Update UI
   connect(&CalcLink, SIGNAL(IsuCalcDisconnected()), this, SLOT(IsuCalcDisconnected())); // Update UI
   connect(&CalcLink, SIGNAL(Reconnecting()), this, SLOT(IsuCalcReconnecting())); // Update UI
   connect(this, SIGNAL(ChangedIsuCalcSettings(const QString&, quint16, uint)),
           &CalcLink, SLOT(ChangedSettings(const QString&, quint16, uint))); // on settings change
   connect(&CalcLinkThread, SIGNAL(started()), &CalcLink, SLOT(Initialize())); // on thread start
   connect(&CalcLinkThread, SIGNAL(finished()), &CalcLink, SLOT(Uninit())); // on thread stop

   CalcLinkThread.start();
}

void MainWindow::InitOsisDataProxy()
{
   DataProxy.SetDataIf(&DataIf);
   DataProxy.moveToThread(&DataProxyThread);
   connect(&DataIf, SIGNAL(NewData()), &DataProxy, SLOT(ProcessData())); // Update UI
   DataProxyThread.start();
}

void MainWindow::InitProxyServer()
{
   Server.SetProxyIf(&DataProxy);
   Server.moveToThread(&ProxyServerThread);
   connect(&ProxyServerThread, SIGNAL(started()), &Server, SLOT(Initialize())); // on thread start
   connect(&ProxyServerThread, SIGNAL(finished()), &Server, SLOT(Uninit())); // on thread start
   connect(this, SIGNAL(ChangedProxyServerSettings(quint16)), &Server, SLOT(ChangedSettings(quint16))); // on settings change
   connect(this, SIGNAL(DisconnectAllClients()), &Server, SLOT(DisconnectAllClients())); // on settings change
   connect(&Server, SIGNAL(ProxyConnected(quint32)), this, SLOT(NewConnection(quint32))); // on settings change
   connect(&Server, SIGNAL(ProxyDisconnected(quint32)), this, SLOT(ClientDisconnected(quint32))); // on settings change
   connect(&DataProxy, SIGNAL(Distribute(QByteArray*)), &Server, SLOT(NewData(QByteArray*))); // on settings change
   ProxyServerThread.start();
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
   settings.endGroup();

   ui->Connect_PB->setText(MetaCalLinkEnum.valueToKey(Connect));
   ConnStatusUIList.push_back(ui->Connection1_LE);
   ConnStatusUIList.push_back(ui->Connection2_LE);
   ConnStatusUIList.push_back(ui->Connection3_LE);
   ConnStatusUIList.push_back(ui->Connection4_LE);
   ConnStatusUIList.push_back(ui->Connection5_LE);
   ConnStatusUIList.push_back(ui->Connection6_LE);
   emit ChangedIsuCalcSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUShort(),ui->Reconnect_CB->checkState());
   emit ChangedProxyServerSettings(ui->ProxyServerPort_LE->text().toUShort());
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
         emit EstablishConnection();
         break;
      case Cancel:
      case Disconnect:
         emit StopConnection();
         break;
   }
}

void MainWindow::IsuCalcConnected()
{
   SetLinkStatus("Connected", MetaCalLinkEnum.valueToKey(Disconnect), true, false, false);
}

void MainWindow::IsuCalcReconnecting()
{
   SetLinkStatus("Connecting...", MetaCalLinkEnum.valueToKey(Cancel), true, false, false);
}

void MainWindow::IsuCalcDisconnected()
{
   SetLinkStatus("Disconnected", MetaCalLinkEnum.valueToKey(Connect), true, true, true);
}

void MainWindow::NewConnection(quint32 addr)
{
   for (auto label:ConnStatusUIList)
   {
      if (label->text().isEmpty())
      {
         label->setText(QString::number(addr));
         ui->ProxyDisconnect_PB->setEnabled(true);
         label->setStyleSheet("QLabel { background-color : lightgreen; }");
         return;
      }
   }
}

void MainWindow::ClientDisconnected(quint32 addr)
{
   for (auto label:ConnStatusUIList)
   {
      if (!addr || label->text().toUInt() == addr)
      {
         label->setStyleSheet("QLabel { background-color : red; }");
         label->setText("");
         if (addr)
         {
            break;
         }
      }
   }
   if (!addr)
   {
      ui->ProxyDisconnect_PB->setEnabled(false);
   }
}

void MainWindow::SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled)
{
   ui->IsuCalcLinkStatus->setText(label);
   ui->Connect_PB->setText(buttonText);
   ui->Connect_PB->setEnabled(buttonEnabled);
   ui->IsuCalcIP_LE->setEnabled(ipAddrEnabled);
   ui->IsuCalcPort_LE->setEnabled(ipPortEnabled);
}

void MainWindow::on_Reconnect_CB_stateChanged(int /*arg1*/)
{
   emit ChangedIsuCalcSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUShort(),ui->Reconnect_CB->checkState());
}

void MainWindow::on_ProxyServerPort_LE_editingFinished()
{
   emit ChangedProxyServerSettings(ui->ProxyServerPort_LE->text().toUShort());
}

void MainWindow::on_ProxyDisconnect_PB_clicked()
{
   DisconnectAllClients();
}
