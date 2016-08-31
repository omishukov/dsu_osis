#include <osis_unittest.h>


void UnittestTest::ObsParseGlobalIni()
{
   QSettings settings(QSettings::IniFormat, QSettings::UserScope, "obs-studio", "global");
   QString SceneFile = settings.value("Basic/SceneCollectionFile").toString();
   qDebug() << "QBS Scene file " << SceneFile + ".json" << endl;

   QString val;
   QFile file;
   QString fileName = "obs-studio/basic/scenes/" + SceneFile + ".json";
   fileName = QStandardPaths::locate(QStandardPaths::AppDataLocation, fileName);
   file.setFileName(fileName);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   val = file.readAll();
   file.close();
   //qWarning() << val;
   QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
   QJsonObject jroot = jsonResponse.object();
   QJsonArray jSceneOrder = jroot["scene_order"].toArray();

   static QStringList specialKeys;
   specialKeys << "control" << "alt" << "shift" << "command";
   enum {
      SS_CONTROL = 0,
      SS_ALT,
      SS_SHIFT,
      SS_COMMAND
   };
   QList<QString> SceneNames;
   foreach (const QJsonValue & jvSceneName, jSceneOrder)
   {
       QJsonObject jScene = jvSceneName.toObject();
       SceneNames.append(jScene["name"].toString());
       qWarning() << jScene["name"].toString();
   }
   QJsonArray jSources = jroot["sources"].toArray();
   foreach (const QJsonValue & jvSource, jSources)
   {
      QJsonObject jScource = jvSource.toObject();
      if (SceneNames.contains(jScource["name"].toString()))
      {
         qWarning() << jScource["name"].toString();
         //Process Hotkeys
         // See OBS get_virtual_key()
         //	save_modifier(modifiers, hotkey, "shift", INTERACT_SHIFT_KEY);
         // save_modifier(modifiers, hotkey, "control", INTERACT_CONTROL_KEY);
         // save_modifier(modifiers, hotkey, "alt", INTERACT_ALT_KEY);
         // save_modifier(modifiers, hotkey, "command", INTERACT_COMMAND_KEY);
         // obs_data_set_string(hotkey, "key", obs_key_to_name(binding->key.key));
         QJsonObject jHotkeys = jScource["hotkeys"].toObject();
         QJsonArray jHotkeyArray = jHotkeys["OBSBasic.SelectScene"].toArray();
         foreach (const QJsonValue & jvHotkey, jHotkeyArray)
         {
            QJsonObject jKeyList = jvHotkey.toObject();;
            QStringList keyList = jKeyList.keys();
            for (auto key : keyList)
            {
               if (specialKeys.contains(key))
               {
                  bool value = jKeyList[key].toBool();
                  if (value)
                  {
                  }
               }
               qWarning() << key;
               qWarning() << jKeyList[key].toString();
            }
         }
      }
   }
}

void UnittestTest::ObsParseTransitionIni()
{
   ObsSceneSwitcher* oss = new ObsSceneSwitcher(new Actions(), "c:/Users/Oleksander/AppData/Roaming/obs-studio");
   oss->LoadObsConfiguration();
   oss->LoadObsTransition();
}
