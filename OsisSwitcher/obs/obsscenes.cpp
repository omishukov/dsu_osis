#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <windows.h>
#include "obsscenes.h"

ObsScenes::ObsScenes(QObject *parent)
   : QObject(parent)
   , MetaObsKeyEnum(QMetaEnum::fromType<obs_key>())
{

}

void ObsScenes::LoadScenes(QString obsconfig)
{
   QString obsJson = ReadConfigurationFile(obsconfig);
   if (obsJson.isEmpty())
   {
      qCritical() << "Can't read from OBS Scene file " << obsconfig; return;
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

QString ObsScenes::ReadConfigurationFile(QString& sceneFile)
{
   QFile file(sceneFile);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   return file.readAll();

}

QList<int> ObsScenes::GetHotkeys(QJsonArray& jHotkeyArray)
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
               int code = MetaObsKeyEnum.keyToValue(jKeyList[key].toString().toLocal8Bit().constData());
               if (code != -1)
               {
                  hotkeys.push_back(GetVirtualKey(code));
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

int ObsScenes::GetVirtualKey(int key)
{
   switch (key)
   {
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
