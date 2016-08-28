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
#include <QFileDialog>
#include "trace.h"
#include "isucompetition.h"
#include "obs/actions.h"
#include "obs/sceneswitcher.h"
#include "obs/actions.h"

QString inifile = "osisc.ini";
extern bool logopt[];

MainWindow::MainWindow(QString logName, QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   ConnectionType(SERVER),
   IpAddress("127.0.0.1"),
   IpPort("0")
{
   ui->setupUi(this);

   setIpValitation();

   loadSettings();

   QFileInfo fi(logName);
   QString logText("Logging to ");
   logText.append(fi.fileName());
   ui->Logging->setTitle(logText);

   Competition = new IsuCompetition();

   OsisLink.setDataIf(Competition->GetDataIf());

   connect(&OsisLink, SIGNAL(UpdateConnectionState()), this, SLOT(showConnectionState()));

   SceneSwitcherThread = new QThread;
   SceneSwitcher = new ObsSceneSwitcher(Competition->GetOsisActions());
   SceneSwitcher->moveToThread(SceneSwitcherThread);
   SceneSwitcherThread->start();
}

MainWindow::~MainWindow()
{
   writeSettings();
   delete ui;
   delete Competition;
   SceneSwitcherThread->quit();
   SceneSwitcherThread->wait();
   delete SceneSwitcherThread;
   delete SceneSwitcher;
}

void MainWindow::loadSettings()
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

   ui->LogDataCB->setChecked(logopt[LOG_DATA]);
   ui->LogErrorCB->setChecked(logopt[LOG_ERROR]);
   ui->LogWarningCB->setChecked(logopt[LOG_WARN]);
   ui->LogDebugCB->setChecked(logopt[LOG_DEBUG]);

   QDir dir(OBS_Path);
   dir.setFilter(QDir::Hidden);
   if (!dir.exists())
   {
      OBS_Path.clear();
   }
   ui->ObsConfigPathLabel->setText(OBS_Path);
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
   logopt[LOG_DEBUG] = settings.value("Debug", false).toBool();
   settings.endGroup();

   settings.beginGroup("MainWindow");
   resize(settings.value("size", QSize(400, 400)).toSize());
   move(settings.value("pos", QPoint(200, 200)).toPoint());
   settings.endGroup();

   settings.beginGroup("OBS");
//   OBS_Path = settings.value("CONFIGURATION_PATH","\%APPDATA\%/obs-studio/").toString();
   OBS_Path = settings.value("CONFIGURATION_PATH","").toString();
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
   settings.setValue("Debug", logopt[LOG_DEBUG]);
   settings.endGroup();

   settings.beginGroup("MainWindow");
   settings.setValue("size", size());
   settings.setValue("pos", pos());
   settings.endGroup();

   settings.beginGroup("OBS");
   settings.setValue("CONFIGURATION_PATH",OBS_Path);
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

void MainWindow::on_LogErrorCB_stateChanged(int arg1)
{
   logopt[LOG_ERROR] = arg1 > 0;
}

void MainWindow::on_LogWarningCB_stateChanged(int arg1)
{
   logopt[LOG_WARN] = arg1 > 0;
}

void MainWindow::on_LogDebugCB_stateChanged(int arg1)
{
   logopt[LOG_DEBUG] = arg1 > 0;
}

void MainWindow::on_ChangeObsConfigPathPB_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select OBS configuration file", OBS_Path, "OBS (global.ini)");
    if (QFileInfo(file_name).exists())
    {
      OBS_Path = QFileInfo(file_name).absolutePath();
      ui->ObsConfigPathLabel->setText(OBS_Path);
    }
}
