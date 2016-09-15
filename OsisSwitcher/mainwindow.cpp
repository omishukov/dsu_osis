#include <QSettings>
#include <QStandardPaths>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaEnum>
#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString inifile = "osisproxy.ini";

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , MetaCalLinkEnum(QMetaEnum::fromType<IsuCalcLinkButton>())
   , CalcIpValidator(0)
   , PortValidator(0)
   , ObsDataSaver(&Action2Scene)
   , TableModel(0)
   , Switcher(&Action2Scene)
{
   ui->setupUi(this);

   InitIsuCalcLink();
   InitOsisParser();
   InitObsData();
   ReadSettings();

   Action2Scene.LoadSceneConfiguration(GetObsSceneFile());
   Action2Scene.LoadActionConfiguration(inifile);
   InitActionSceneUi();

   InitSceneSwitcher();
}

MainWindow::~MainWindow()
{
   SaveSettings();

   CalcLinkThread.quit();
   CalcLinkThread.wait();
   OsisDataParserThread.quit();
   OsisDataParserThread.wait();
   ObsDataSaverThread.quit();
   ObsDataSaverThread.wait();
   SwitcherThread.quit();
   SwitcherThread.wait();

   delete CalcIpValidator;
   delete PortValidator;
   delete TableModel;
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
   settings.endGroup();

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
    settings.endGroup();
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

void MainWindow::InitOsisParser()
{
   OsisDataParser.SetDataIf(&DataIf);
   OsisDataParser.SetObsDataSaver(&ObsDataSaver);
   OsisDataParser.moveToThread(&OsisDataParserThread);
   connect(&DataIf, SIGNAL(NewData()), &OsisDataParser, SLOT(ProcessData())); // Update UI
   connect(&OsisDataParserThread, SIGNAL(started()), &OsisDataParser, SLOT(Initialize())); // on thread start
   connect(&OsisDataParserThread, SIGNAL(finished()), &OsisDataParser, SLOT(Uninit())); // on thread stop
   OsisDataParserThread.start();
}

void MainWindow::InitObsData()
{
   ObsDataSaver.moveToThread(&ObsDataSaverThread);

   connect(&ObsDataSaver, SIGNAL(SendOsisEvent(int)), &Switcher, SLOT(HandleEvent(int))); // on thread start
   ObsDataSaverThread.start();
}

void MainWindow::InitSceneSwitcher()
{
   Switcher.moveToThread(&SwitcherThread);
   SwitcherThread.start();
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
   TableGui.SetObsActions(&Action2Scene);

   TableModel = new QStandardItemModel(ActionToScene::LAST_ACTION - 1, 6);
   ui->ActionToSceneQTV->setModel(TableModel);
   TableModel->setHorizontalHeaderLabels(QString("Event;Delay;Scene1;Delay;Scene2;Transition").split(";"));
   ui->ActionToSceneQTV->setItemDelegate(&TableGui);

   int row = 0;
   Action2SceneStruct Action;
   for(int i = ActionToScene::NO_ACTIONS + 1; i < ActionToScene::LAST_ACTION; i++)
   {
      Action = Action2Scene.GetActionSceneInfo(i);
      QModelIndex index0 = TableModel->index(row, 0, QModelIndex());
      QModelIndex index1 = TableModel->index(row, 1, QModelIndex());
      QModelIndex index2 = TableModel->index(row, 2, QModelIndex());
      QModelIndex index3 = TableModel->index(row, 3, QModelIndex());
      QModelIndex index4 = TableModel->index(row, 4, QModelIndex());
      QModelIndex index5 = TableModel->index(row, 5, QModelIndex());

      TableModel->setData(index0, QVariant(Action.ActionName));
      TableModel->setData(index1, QVariant(Action.Delay));
      TableModel->setData(index2, QVariant(Action.Scene));
      TableModel->setData(index3, QVariant(Action.NextDelay));
      TableModel->setData(index4, QVariant(Action.NextScene));
      TableModel->setData(index5, QVariant(Action.Transition));

      row++;
   }
   ui->ActionToSceneQTV->resizeColumnsToContents();
   ui->ActionToSceneQTV->show();
}
