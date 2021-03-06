#include <QSettings>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMetaEnum>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString inifile = "osisc.ini";

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , MetaCalLinkEnum(QMetaEnum::fromType<IsuCalcLinkButton>())
   , TableGui(0)
{
   ui->setupUi(this);

   QString version(GIT_VERSION);
   setWindowTitle("DSU OBS Switcher " + version);

   ReadSettings();

   InitIsuCalcLink();

   OsisDataParser.SetDataIf(&OsisDataQueue);
   OsisDataParser.moveToThread(&OsisIfThread);

   ObsStreamIf = new ObsSceneSwitcher(OBS_Path, OsisDataParser.GetOsisIf());
   ObsStreamIf->moveToThread(&StreamIfThread);
   OsisDataParser.SetStreamIf(ObsStreamIf);

   StreamIfThread.start();
   OsisIfThread.start();

   InitActionSceneUi();
}

MainWindow::~MainWindow()
{
   SaveSettings();

   CalcLinkThread.quit();
   CalcLinkThread.wait();
   OsisIfThread.quit();
   OsisIfThread.wait();
   StreamIfThread.quit();
   StreamIfThread.wait();

   delete ObsStreamIf;
   delete TableGui;
   delete ui;
}

void MainWindow::ReadSettings()
{
   setIpValitation();
   QSettings settings(inifile, QSettings::IniFormat);

   settings.beginGroup("Connection");
   ui->IsuCalcIP_LE->setText(settings.value("isu_calc_ip", "127.0.0.1").toString());
   ui->IsuCalcPort_LE->setText(settings.value("isu_calc_port", "4000").toString());
   ui->Reconnect_CB->setCheckState(settings.value("isu_calc_recon", false).toBool()?Qt::Checked:Qt::Unchecked);
   settings.endGroup();

   settings.beginGroup("OBS");
   QSettings obs_settings(QSettings::IniFormat, QSettings::UserScope, "obs-studio", "global");
   QString location;
   if (QFileInfo(obs_settings.fileName()).exists())
   {
      location = QFileInfo(obs_settings.fileName()).absolutePath() + "/";
   }
   location = settings.value("OBS_CONFIG", location).toString();
   if (QFileInfo(location).exists())
   {
      ui->ObsConfigPathLabel->setText(settings.value("OBS_CONFIG", location).toString());
      OBS_Path = location;
   }
   else
   {
      OBS_Path = QFileInfo(obs_settings.fileName()).absolutePath() + "/";
   }

   CurrentTransition = settings.value("OBS_TRANSITION", "").toString();

   settings.endGroup();

   ui->ObsConfigPathLabel->setText(OBS_Path);
   ui->Connect_PB->setText(MetaCalLinkEnum.valueToKey(Connect));
   emit ChangedIsuCalcSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUShort(),ui->Reconnect_CB->checkState());
}

void MainWindow::SaveSettings()
{
    QSettings settings(inifile, QSettings::IniFormat);

    settings.beginGroup("Connection");
    settings.setValue("isu_calc_ip", ui->IsuCalcIP_LE->text());
    settings.setValue("isu_calc_port", ui->IsuCalcPort_LE->text());
    settings.setValue("isu_calc_recon", ui->Reconnect_CB->checkState());
    settings.endGroup();
    settings.beginGroup("OBS");
    settings.setValue("OBS_CONFIG", OBS_Path);
    settings.setValue("OBS_TRANSITION", CurrentTransition);
    settings.endGroup();
}

void MainWindow::setIpValitation()
{
   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   ui->IsuCalcIP_LE->setValidator(new QRegExpValidator(ipRegex, this));
   ui->IsuCalcPort_LE->setValidator(new QIntValidator(6,65535,this));//ports
}

void MainWindow::InitIsuCalcLink()
{
   CalcLink.SetDataIf(&OsisDataQueue);
   CalcLink.moveToThread(&CalcLinkThread);

   connect(this, SIGNAL(EstablishConnection()), &CalcLink, SLOT(Establish()), Qt::QueuedConnection); // Connect to the IsuCalc
   connect(this, SIGNAL(StopConnection()), &CalcLink, SLOT(StopConnection()), Qt::QueuedConnection); // Disconnect from the IsuCalc
   connect(&CalcLink, SIGNAL(Established()), this, SLOT(IsuCalcConnected()), Qt::QueuedConnection); // Update UI
   connect(&CalcLink, SIGNAL(IsuCalcDisconnected()), this, SLOT(IsuCalcDisconnected()), Qt::QueuedConnection); // Update UI
   connect(&CalcLink, SIGNAL(Reconnecting()), this, SLOT(IsuCalcReconnecting()), Qt::QueuedConnection); // Update UI
   connect(this, SIGNAL(ChangedIsuCalcSettings(const QString&, quint16, uint)),
           &CalcLink, SLOT(ChangedSettings(const QString&, quint16, uint)), Qt::QueuedConnection); // on settings change
   connect(&CalcLinkThread, SIGNAL(started()), &CalcLink, SLOT(Initialize()), Qt::QueuedConnection); // on thread start
   connect(&CalcLinkThread, SIGNAL(finished()), &CalcLink, SLOT(Uninit()), Qt::QueuedConnection); // on thread stop

   CalcLinkThread.start();
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

void MainWindow::SetLinkStatus(QString label, QString buttonText, bool buttonEnabled, bool ipAddrEnabled, bool ipPortEnabled)
{
   ui->IsuCalcLinkStatus->setText(label);
   if (!QString::compare(label, "Connected"))
   {
      ui->IsuCalcLinkStatus->setStyleSheet("QLabel { background-color : lightgreen; }");
   }
   else if (!QString::compare(label, "Connecting..."))
   {
      ui->IsuCalcLinkStatus->setStyleSheet("QLabel { background-color : lightyellow; }");
   }
   else if (!QString::compare(label, "Disconnected"))
   {
      ui->IsuCalcLinkStatus->setStyleSheet("QLabel { background-color : red; }");
   }
   ui->Connect_PB->setText(buttonText);
   ui->Connect_PB->setEnabled(buttonEnabled);
   ui->IsuCalcIP_LE->setEnabled(ipAddrEnabled);
   ui->IsuCalcPort_LE->setEnabled(ipPortEnabled);
}

void MainWindow::on_Reconnect_CB_stateChanged(int /*arg1*/)
{
   emit ChangedIsuCalcSettings(ui->IsuCalcIP_LE->text(),ui->IsuCalcPort_LE->text().toUShort(),ui->Reconnect_CB->checkState());
}

QString MainWindow::GetObsSceneFile()
{
   QString global_ini = OBS_Path + "/global.ini";
   QSettings settings(global_ini, QSettings::IniFormat);
   QString SceneFile = settings.value("Basic/SceneCollectionFile").toString();
   return OBS_Path + "/basic/scenes/" + SceneFile + ".json";
}

void MainWindow::InitActionSceneUi()
{
   QStringList NameList = ObsStreamIf->GetTransitions();
   ui->TransitionCB->addItems(NameList);
   int index = ui->TransitionCB->findText(CurrentTransition);
   if ( index != -1 )
   {
      ui->TransitionCB->setCurrentIndex(index);
   }
   ObsStreamIf->SetTransition(CurrentTransition);

   TableGui = new SwitcherConfig(inifile, OsisDataParser.GetOsisIf(), ObsStreamIf, ui->ActionToSceneQTV);
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

void MainWindow::on_TransitionCB_currentIndexChanged(const QString &arg1)
{
    CurrentTransition = arg1;
    ObsStreamIf->SetTransition(CurrentTransition);
}
