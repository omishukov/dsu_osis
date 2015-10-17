//---------------------------------- //
// Open Scoring Interface Controller //
//---------------------------------- //

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QSettings>
#include <QtNetwork>

const QString inifile = "osisc.ini";

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   ConnectionType(SERVER),
   IpAddress("127.0.0.1"),
   IpPort("0")
{
   ui->setupUi(this);

   setIpValitation();

   loadConnectionSettings();
}

MainWindow::~MainWindow()
{
   writeSettings();
   delete ui;
}

void MainWindow::loadConnectionSettings()
{
   readSettings();

   if (ConnectionType == CLIENT)
   {
      ui->IPv4Address->setText(IpAddress);
   }
   else // SERVER
   {
      // find out which IP to connect to
      QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
      // use the first non-localhost IPv4 address
      for (int i = 0; i < ipAddressesList.size(); ++i)
      {
         if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
         {
            IpAddress = ipAddressesList.at(i).toString();
            break;
          }
      }
      ui->IPv4Address->setText(IpAddress);
   }
   ui->IPv4Port->setText(IpPort);
}

void MainWindow::setIpValitation()
{
   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   QValidator *ipValidator = new QRegExpValidator(ipRegex, this);
   ui->IPv4Address->setValidator(ipValidator);

   QValidator* validator = new QIntValidator(6,65535,this);// 0 to 65535
   ui->IPv4Port->setValidator(validator);//ports
}

void MainWindow::readSettings()
{
   QSettings settings(inifile, QSettings::IniFormat);

   settings.beginGroup("Connection");
   ConnectionType = ConnectAs(settings.value("mode", SERVER).toInt());
   IpAddress = settings.value("address", "127.0.0.1").toString();
   IpPort = settings.value("port", "0").toString();
   settings.endGroup();

   settings.beginGroup("MainWindow");
   resize(settings.value("size", QSize(400, 400)).toSize());
   move(settings.value("pos", QPoint(200, 200)).toPoint());
   settings.endGroup();
}

void MainWindow::writeSettings()
{
   QSettings settings(inifile, QSettings::IniFormat);

   settings.beginGroup("Connection");
   settings.setValue("mode", ConnectionType);
   settings.setValue("address", IpAddress);
   settings.setValue("port", IpPort);
   settings.endGroup();

   settings.beginGroup("MainWindow");
   settings.setValue("size", size());
   settings.setValue("pos", pos());
   settings.endGroup();
}
