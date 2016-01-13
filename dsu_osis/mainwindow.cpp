/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

//---------------------------------- //
// Open Scoring Interface Controller //
//---------------------------------- //

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QSettings>
#include <QtNetwork>
#include <QTextStream>

const QString inifile = "osisc.ini";

const int LOG_DATA = 0;
const int LOG_ERROR = 1;
const int LOG_WARN = 2;
bool logopt[3] = {false, false, false}; // data, error, warning

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

   OsisData = new OsisDataProvider();

   OsisLink.setDataIf(OsisData);

   connect(&OsisLink, SIGNAL(UpdateConnectionState()), this, SLOT(showConnectionState()));

   f = new QFile("osislog.txt");
   if (f->open(QIODevice::ReadWrite | QIODevice::Text))
   {
      if (!f->isSequential())
      {
          f->seek(f->size());
      }
      OsisLink.SetLogIf(new QTextStream(f));
   }
}

MainWindow::~MainWindow()
{
   f->close();
   writeSettings();
   delete ui;
}

void MainWindow::loadConnectionSettings()
{
   readSettings();

   if (ui->ClientServerCB->currentIndex() != ConnectionType)
   {
      ui->ClientServerCB->setCurrentIndex(ConnectionType);
   }

   if (ConnectionType == CLIENT)
   {
      ui->IPv4Address->setText(IpAddress);
   }
   else // SERVER
   {
      ui->IPv4Address->clear();
      ui->IPv4Address->setDisabled(true);
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

   settings.beginGroup("Logging");
   logopt[LOG_DATA] = settings.value("Data", false).toBool();
   logopt[LOG_ERROR] = settings.value("Error", false).toBool();
   logopt[LOG_WARN] = settings.value("Warning", false).toBool();
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

   settings.beginGroup("Logging");
   settings.setValue("Data", logopt[LOG_DATA]);
   settings.setValue("Error", logopt[LOG_ERROR]);
   settings.setValue("Warning", logopt[LOG_WARN]);
   settings.endGroup();

   settings.beginGroup("MainWindow");
   settings.setValue("size", size());
   settings.setValue("pos", pos());
   settings.endGroup();
}

void MainWindow::on_ClientServerCB_activated(int index)
{
   if (index != ConnectionType)
   {
      ConnectionType = ConnectAs(index);

      if (ConnectionType == CLIENT)
      {
         ConnectionType = CLIENT;
         ui->IPv4Address->setText(IpAddress);
         ui->IPv4Address->setDisabled(false);
      }
      else if (ConnectionType == SERVER)
      {
         ConnectionType = SERVER;
         ui->IPv4Address->clear();
         ui->IPv4Address->setDisabled(true);
      }
   }
}

void MainWindow::on_ConnectButton_clicked()
{
   switch (OsisLink.GetState())
   {
      case CalcConnectionThread::DISCONNECTED:
         {
            ui->ConnectionStatusLabel->setText("Connecting...");
            ui->ConnectButton->setEnabled(false);
            OsisLink.establishConnection(ConnectionType == CLIENT? IpAddress : "", IpPort.toUShort());
         }
         break;

      case CalcConnectionThread::CONNECTING:
      case CalcConnectionThread::CONNECTED:
         {  //Abort connection attempt
            ui->ConnectionStatusLabel->setText("Aborting...");
            ui->ConnectButton->setEnabled(false);
            OsisLink.abortConnection();
         }
         break;

      default:
         break;
   }
}

void MainWindow::showConnectionState()
{
   switch(OsisLink.GetState())
   {
      case CalcConnectionThread::CONNECTING:
         {
            ui->ConnectionStatusLabel->setText("Connecting...");
            ui->ConnectButton->setText("Cancel");
            ui->ConnectButton->setEnabled(true);
            ui->ClientServerCB->setEnabled(false);
            ui->IPv4Address->setEnabled(false);
            ui->IPv4Port->setEnabled(false);
         }
         break;
      case CalcConnectionThread::DISCONNECTED:
         {
            ui->ConnectionStatusLabel->setText("Disconnected");
            ui->ConnectButton->setText("Connect");
            ui->ConnectButton->setEnabled(true);
            ui->ClientServerCB->setEnabled(true);
            ui->IPv4Address->setEnabled(true);
            ui->IPv4Port->setEnabled(true);
         }
         break;
      case CalcConnectionThread::CONNECTED:
         {
            ui->ConnectionStatusLabel->setText("Connected");
            ui->ConnectButton->setText("Disconnect");
            ui->ConnectButton->setEnabled(true);
         }
         break;
      default:
         break;
   }

}

void MainWindow::on_IPv4Address_editingFinished()
{
   IpAddress = ui->IPv4Address->text();
}

void MainWindow::on_IPv4Port_editingFinished()
{
    IpPort = ui->IPv4Port->text();
}

void MainWindow::on_LogDataCB_stateChanged(int arg1)
{
   logopt[LOG_DATA] = arg1 > 0;
}
