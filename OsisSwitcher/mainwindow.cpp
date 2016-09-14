#include <QSettings>
#include <QStandardPaths>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaEnum>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

QString inifile = "osisproxy.ini";

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , MetaCalLinkEnum(QMetaEnum::fromType<IsuCalcLinkButton>())
   , CalcIpValidator(0)
   , PortValidator(0)
   , MetaActionsEnum(QMetaEnum::fromType<obs_key>())
   , TableModel(0)
{
   ui->setupUi(this);
   InitIsuCalcLink();
   InitOsisParser();
   InitObsData();
   ReadSettings();

   LoadObsConfiguration();
   LoadSceneConfiguration();
   InitActionSceneUi();
}

MainWindow::~MainWindow()
{
   SaveSettings();
   SaveSceneConfiguration();

   CalcLinkThread.quit();
   CalcLinkThread.wait();
   OsisDataParserThread.quit();
   OsisDataParserThread.wait();
   ObsDataSaverThread.quit();
   ObsDataSaverThread.wait();

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

//   connect(&ObsDataSaver, SIGNAL(SendOsisEvent(int)), &Switcher, SLOT(HandleEvent())); // on thread start
   ObsDataSaverThread.start();
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

QString MainWindow::ReadObsConfiguration(QString& sceneFile)
{
   QFile file(sceneFile);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   return file.readAll();
}

void MainWindow::LoadObsConfiguration()
{
   QString SceneFile = GetObsSceneFile();
   if (SceneFile.isEmpty())
   {
      qCritical() << "OBS Scene file " << SceneFile << " not found"; return;
   }

   QString obsJson = ReadObsConfiguration(SceneFile);
   if (obsJson.isEmpty())
   {
      qCritical() << "Can't read from OBS Scene file " << SceneFile; return;
   }

   qInfo() << "Read active OBS scenes and transitions:";
   QList<QString> ActiveScenes;
   QJsonDocument jsonResponse = QJsonDocument::fromJson(obsJson.toUtf8());
   QJsonObject jroot = jsonResponse.object();
   QJsonArray jSceneOrder = jroot["scene_order"].toArray();
   foreach (const QJsonValue& jvSceneName, jSceneOrder)
   {
       QJsonObject jScene = jvSceneName.toObject();
       ActiveScenes.append(jScene["name"].toString());
       qInfo() << jScene["name"].toString();
   }

   // Find scenes and associate with hotkeys
   QJsonArray jSources = jroot["sources"].toArray();
   foreach (const QJsonValue & jvSource, jSources)
   {
      QJsonObject jScource = jvSource.toObject();
      if (ActiveScenes.contains(jScource["name"].toString()))
      {
         QString SceneName = jScource["name"].toString();
         QJsonObject jHotkeys = jScource["hotkeys"].toObject();
         QJsonArray jHotkeyArray = jHotkeys["OBSBasic.SelectScene"].toArray();

         QList<int> hotkeys = GetHotkeys(jHotkeyArray);

         if (hotkeys.count())
         {
            SceneHkeyMap.insert(SceneName, hotkeys);
         }
         else
         {
            qWarning() << SceneName << " scene doesn't have hotkeys";
         }
      }
   }
   // Find transitions and associate with hotkeys
   QJsonArray jTtransitions = jroot["quick_transitions"].toArray();
   foreach (const QJsonValue& jvTransition, jTtransitions)
   {
      QJsonObject jTransition = jvTransition.toObject();
      QString TransitionName = jTransition["name"].toString();
      qInfo() << TransitionName;

      QJsonArray jHotkeys = jTransition["hotkeys"].toArray();

      QList<int> hotkeys = GetHotkeys(jHotkeys);

      if (hotkeys.count())
      {
         TransitionHkeyMap.insert(TransitionName, hotkeys);
      }
      else
      {
         qWarning() << TransitionName << " transition doesn't have hotkeys";
      }
   }
   if (SceneHkeyMap.isEmpty() || TransitionHkeyMap.isEmpty())
   {
      qCritical() << "There is no Active Scenes or Transitions congigured. Scene Switch will not work";
   }
}

QList<int> MainWindow::GetHotkeys(QJsonArray& jHotkeyArray)
{
   static QStringList specialKeys;
   specialKeys << "control" << "alt" << "shift" << "command" << "key";
   QList<int> hotkeys;
   foreach (const QJsonValue & jvHotkey, jHotkeyArray)
   {
      QJsonObject jKeyList = jvHotkey.toObject();;
      QStringList keyList = jKeyList.keys();
      for (auto key : keyList)
      {
         if (specialKeys.contains(key, Qt::CaseInsensitive))
         {
            if (!QString::compare(key, "control", Qt::CaseInsensitive) && jKeyList[key].toBool())
            {
               hotkeys.push_back(VK_CONTROL);
            }
            else if (!QString::compare(key, "alt", Qt::CaseInsensitive) && jKeyList[key].toBool())
            {
               hotkeys.push_back(VK_MENU);
            }
            else if (!QString::compare(key, "shift", Qt::CaseInsensitive) && jKeyList[key].toBool())
            {
               hotkeys.push_back(VK_SHIFT);
            }
            else if (!QString::compare(key, "key", Qt::CaseInsensitive))
            {
               int code = MetaActionsEnum.keyToValue(jKeyList[key].toString().toLocal8Bit().constData());
               if (code != -1)
               {
                  hotkeys.push_back(get_virtual_key(code));
               }
            }
         }
      }
      if (hotkeys.size())
      {
         // Take first hotkeys
         break;
      }
   }
   return hotkeys;
}

int MainWindow::get_virtual_key(int key)
{
   switch (key) {
   case OBS_KEY_RETURN: return VK_RETURN;
   case OBS_KEY_ESCAPE: return VK_ESCAPE;
   case OBS_KEY_TAB: return VK_TAB;
   case OBS_KEY_BACKTAB: return VK_OEM_BACKTAB;
   case OBS_KEY_BACKSPACE: return VK_BACK;
   case OBS_KEY_INSERT: return VK_INSERT;
   case OBS_KEY_DELETE: return VK_DELETE;
   case OBS_KEY_PAUSE: return VK_PAUSE;
   case OBS_KEY_PRINT: return VK_SNAPSHOT;
   case OBS_KEY_CLEAR: return VK_CLEAR;
   case OBS_KEY_HOME: return VK_HOME;
   case OBS_KEY_END: return VK_END;
   case OBS_KEY_LEFT: return VK_LEFT;
   case OBS_KEY_UP: return VK_UP;
   case OBS_KEY_RIGHT: return VK_RIGHT;
   case OBS_KEY_DOWN: return VK_DOWN;
   case OBS_KEY_PAGEUP: return VK_PRIOR;
   case OBS_KEY_PAGEDOWN: return VK_NEXT;

   case OBS_KEY_SHIFT: return VK_SHIFT;
   case OBS_KEY_CONTROL: return VK_CONTROL;
   case OBS_KEY_ALT: return VK_MENU;
   case OBS_KEY_CAPSLOCK: return VK_CAPITAL;
   case OBS_KEY_NUMLOCK: return VK_NUMLOCK;
   case OBS_KEY_SCROLLLOCK: return VK_SCROLL;

   case OBS_KEY_F1: return VK_F1;
   case OBS_KEY_F2: return VK_F2;
   case OBS_KEY_F3: return VK_F3;
   case OBS_KEY_F4: return VK_F4;
   case OBS_KEY_F5: return VK_F5;
   case OBS_KEY_F6: return VK_F6;
   case OBS_KEY_F7: return VK_F7;
   case OBS_KEY_F8: return VK_F8;
   case OBS_KEY_F9: return VK_F9;
   case OBS_KEY_F10: return VK_F10;
   case OBS_KEY_F11: return VK_F11;
   case OBS_KEY_F12: return VK_F12;
   case OBS_KEY_F13: return VK_F13;
   case OBS_KEY_F14: return VK_F14;
   case OBS_KEY_F15: return VK_F15;
   case OBS_KEY_F16: return VK_F16;
   case OBS_KEY_F17: return VK_F17;
   case OBS_KEY_F18: return VK_F18;
   case OBS_KEY_F19: return VK_F19;
   case OBS_KEY_F20: return VK_F20;
   case OBS_KEY_F21: return VK_F21;
   case OBS_KEY_F22: return VK_F22;
   case OBS_KEY_F23: return VK_F23;
   case OBS_KEY_F24: return VK_F24;

   case OBS_KEY_SPACE: return VK_SPACE;

   case OBS_KEY_APOSTROPHE: return VK_OEM_7;
   case OBS_KEY_PLUS: return VK_OEM_PLUS;
   case OBS_KEY_COMMA: return VK_OEM_COMMA;
   case OBS_KEY_MINUS: return VK_OEM_MINUS;
   case OBS_KEY_PERIOD: return VK_OEM_PERIOD;
   case OBS_KEY_SLASH: return VK_OEM_2;
   case OBS_KEY_0: return '0';
   case OBS_KEY_1: return '1';
   case OBS_KEY_2: return '2';
   case OBS_KEY_3: return '3';
   case OBS_KEY_4: return '4';
   case OBS_KEY_5: return '5';
   case OBS_KEY_6: return '6';
   case OBS_KEY_7: return '7';
   case OBS_KEY_8: return '8';
   case OBS_KEY_9: return '9';
   case OBS_KEY_NUMASTERISK: return VK_MULTIPLY;
   case OBS_KEY_NUMPLUS: return VK_ADD;
   case OBS_KEY_NUMMINUS: return VK_SUBTRACT;
   case OBS_KEY_NUMPERIOD: return VK_DECIMAL;
   case OBS_KEY_NUMSLASH: return VK_DIVIDE;
   case OBS_KEY_NUM0: return VK_NUMPAD0;
   case OBS_KEY_NUM1: return VK_NUMPAD1;
   case OBS_KEY_NUM2: return VK_NUMPAD2;
   case OBS_KEY_NUM3: return VK_NUMPAD3;
   case OBS_KEY_NUM4: return VK_NUMPAD4;
   case OBS_KEY_NUM5: return VK_NUMPAD5;
   case OBS_KEY_NUM6: return VK_NUMPAD6;
   case OBS_KEY_NUM7: return VK_NUMPAD7;
   case OBS_KEY_NUM8: return VK_NUMPAD8;
   case OBS_KEY_NUM9: return VK_NUMPAD9;
   case OBS_KEY_SEMICOLON: return VK_OEM_1;
   case OBS_KEY_A: return 'A';
   case OBS_KEY_B: return 'B';
   case OBS_KEY_C: return 'C';
   case OBS_KEY_D: return 'D';
   case OBS_KEY_E: return 'E';
   case OBS_KEY_F: return 'F';
   case OBS_KEY_G: return 'G';
   case OBS_KEY_H: return 'H';
   case OBS_KEY_I: return 'I';
   case OBS_KEY_J: return 'J';
   case OBS_KEY_K: return 'K';
   case OBS_KEY_L: return 'L';
   case OBS_KEY_M: return 'M';
   case OBS_KEY_N: return 'N';
   case OBS_KEY_O: return 'O';
   case OBS_KEY_P: return 'P';
   case OBS_KEY_Q: return 'Q';
   case OBS_KEY_R: return 'R';
   case OBS_KEY_S: return 'S';
   case OBS_KEY_T: return 'T';
   case OBS_KEY_U: return 'U';
   case OBS_KEY_V: return 'V';
   case OBS_KEY_W: return 'W';
   case OBS_KEY_X: return 'X';
   case OBS_KEY_Y: return 'Y';
   case OBS_KEY_Z: return 'Z';
   case OBS_KEY_BRACKETLEFT: return VK_OEM_4;
   case OBS_KEY_BACKSLASH: return VK_OEM_5;
   case OBS_KEY_BRACKETRIGHT: return VK_OEM_6;
   case OBS_KEY_ASCIITILDE: return VK_OEM_3;

   case OBS_KEY_KANJI: return VK_KANJI;
   case OBS_KEY_TOUROKU: return VK_OEM_FJ_TOUROKU;
   case OBS_KEY_MASSYO: return VK_OEM_FJ_MASSHOU;

   case OBS_KEY_HANGUL: return VK_HANGUL;

   case OBS_KEY_MOUSE1: return VK_LBUTTON;
   case OBS_KEY_MOUSE2: return VK_RBUTTON;
   case OBS_KEY_MOUSE3: return VK_MBUTTON;
   case OBS_KEY_MOUSE4: return VK_XBUTTON1;
   case OBS_KEY_MOUSE5: return VK_XBUTTON2;

   /* TODO: Implement keys for non-US keyboards */
   default:;
   }
   return 0;
}

void MainWindow::LoadSceneConfiguration()
{
   QSettings settings(inifile, QSettings::IniFormat);
   QString sceneName;

   for(int i = Actions::NO_ACTIONS + 1; i < Actions::LAST_ACTION; i++)
   {
      ActionToScenes[i].ActionName = ObsDataSaver.GetActionName(i);

      settings.beginGroup(ActionToScenes[i].ActionName);

      sceneName = settings.value("SCENE1").toString();
      if (!SceneHkeyMap.contains(sceneName))
      {
         sceneName.clear();
         qWarning() << "Scene [" << sceneName << "] from config file doesn't exist in OBS configuration";
      }
      ActionToScenes[i].Scene = sceneName;
      ActionToScenes[i].Delay = settings.value("DELAY1", "0").toInt();

      sceneName = settings.value("SCENE2").toString();
      if (!SceneHkeyMap.contains(sceneName))
      {
         sceneName.clear();
         qWarning() << "Scene [" << sceneName << "] from config file doesn't exist in OBS configuration";
      }
      ActionToScenes[i].NextScene = sceneName;
      ActionToScenes[i].NextDelay = settings.value("DELAY2", "0").toInt();

      sceneName = settings.value("TRANSITION", "").toString();
      if (!TransitionHkeyMap.contains(sceneName))
      {
         sceneName.clear();
         qWarning() << "Transition [" << sceneName << "] from config file doesn't exist in OBS configuration";
      }
      ActionToScenes[i].Transition = sceneName;

      settings.endGroup();
   }
}

void MainWindow::SaveSceneConfiguration()
{
   QSettings settings(inifile, QSettings::IniFormat);

   for(int i = Actions::NO_ACTIONS + 1; i < Actions::LAST_ACTION; i++)
   {
      if (!ActionToScenes[i].ActionName.isEmpty())
      {
         settings.beginGroup(ActionToScenes[i].ActionName);
         settings.setValue("SCENE1", ActionToScenes[i].Scene);
         settings.setValue("DELAY1", ActionToScenes[i].Delay);
         settings.setValue("SCENE2", ActionToScenes[i].NextScene);
         settings.setValue("DELAY2", ActionToScenes[i].NextDelay);
         settings.setValue("TRANSITION", ActionToScenes[i].Transition);
         settings.endGroup();
      }
   }
}

void MainWindow::InitActionSceneUi()
{
   TableGui.SetObsActions(ActionToScenes);
   TableGui.SetObsScenesList(SceneHkeyMap.uniqueKeys());
   TableGui.SetObsTransitionList(TransitionHkeyMap.uniqueKeys());

   TableModel = new QStandardItemModel(Actions::LAST_ACTION - 1, 6);
   ui->ActionToSceneQTV->setModel(TableModel);
   TableModel->setHorizontalHeaderLabels(QString("Event;Delay;Scene1;Delay;Scene2;Transition").split(";"));
   ui->ActionToSceneQTV->setItemDelegate(&TableGui);

   int row = 0;
   for(int i = Actions::NO_ACTIONS + 1; i < Actions::LAST_ACTION; i++)
   {
      QModelIndex index0 = TableModel->index(row, 0, QModelIndex());
      QModelIndex index1 = TableModel->index(row, 1, QModelIndex());
      QModelIndex index2 = TableModel->index(row, 2, QModelIndex());
      QModelIndex index3 = TableModel->index(row, 3, QModelIndex());
      QModelIndex index4 = TableModel->index(row, 4, QModelIndex());
      QModelIndex index5 = TableModel->index(row, 5, QModelIndex());

      TableModel->setData(index0, QVariant(ActionToScenes[i].ActionName));
      TableModel->setData(index1, QVariant(ActionToScenes[i].Delay));
      TableModel->setData(index2, QVariant(ActionToScenes[i].Scene));
      TableModel->setData(index3, QVariant(ActionToScenes[i].NextDelay));
      TableModel->setData(index4, QVariant(ActionToScenes[i].NextScene));
      TableModel->setData(index5, QVariant(ActionToScenes[i].Transition));

      row++;
   }
// Todo: this crash if no valid OBS Path specified.
   ui->ActionToSceneQTV->resizeColumnsToContents();
   ui->ActionToSceneQTV->show();
}
