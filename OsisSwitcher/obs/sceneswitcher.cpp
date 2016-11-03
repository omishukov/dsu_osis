#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ObsSceneSwitcher::ObsSceneSwitcher(ActionToScene* actions, QObject *parent)
   : QObject(parent)
   , Action2Scene(actions)
   , CurrentAction(0)
{
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
}

void ObsSceneSwitcher::LoadActions(QString& inifile, SwitcherOsisIf* osisIf)
{
   Inifile = inifile;
   QSettings settings(Inifile, QSettings::IniFormat);
   QString sceneName;
   int sceneDelay;

   QMetaEnum metaEnum = QMetaEnum::fromType<SwitcherOsisIf::OSIS_ACTIONS_ENUM>();
   for(int i = SwitcherOsisIf::NO_ACTIONS + 1; i < SwitcherOsisIf::LAST_ACTION; i++)
   {
      QString ActionName = metaEnum.valueToKey(i);
      settings.beginGroup(ActionName);
      QMap<QString, int> SceneDelayMap;

      for (int sc = 1; sc < 3; sc++)
      {
         QString Scene = QString("SCENE%s").arg(sc);
         QString Delay = QString("DELAY%s").arg(sc);
         sceneName = settings.value(Scene, "").toString();
         sceneDelay = settings.value(Delay, "0").toInt();
         SceneDelayMap.insert(sceneName, sceneDelay);
      }
      ObsAction* action = new ObsAction(i, SceneDelayMap, osisIf);
      if (!SceneHkeyMap.contains(sceneName))
      {
         sceneName.clear();
         if (!sceneName.isEmpty())
         {
            qWarning() << "Scene [" << sceneName << "] from config file doesn't exist in OBS configuration";
         }
      }
      else
      {
         ActionToScenes[i].Hkey = SceneHkeyMap.value(sceneName);
      }
      ActionToScenes[i].Scene = sceneName;
      ActionToScenes[i].Delay = settings.value("DELAY1", "0").toInt();

      sceneName = settings.value("SCENE2").toString();
      if (!SceneHkeyMap.contains(sceneName))
      {
         sceneName.clear();
         if (!sceneName.isEmpty())
         {
            qWarning() << "Scene [" << sceneName << "] from config file doesn't exist in OBS configuration";
         }
      }
      else
      {
         ActionToScenes[i].NextHkey = SceneHkeyMap.value(sceneName);
      }
      ActionToScenes[i].NextScene = sceneName;
      ActionToScenes[i].NextDelay = settings.value("DELAY2", "0").toInt();

      settings.endGroup();
   }

}


void ObsSceneSwitcher::HandleEvent(int act)
{
   RemoveCompletesActions();

   Action2SceneStruct info = Action2Scene->GetActionSceneInfo(act);
   if (info.Hkey.isEmpty() || info.TransitionHkey.isEmpty())
   {
      return;
   }

   ObsAction* newAction = new ObsAction(info, !CurrentAction || CurrentAction->Completed()?0:CurrentAction);
   CurrentAction = newAction;
   newAction->Execute();
}

void ObsSceneSwitcher::Initialize()
{
}

void ObsSceneSwitcher::RemoveCompletesActions()
{
   QMutableListIterator<ObsAction*> i(ActiveActions);
   while (i.hasNext())
   {
      if (i.next()->Completed())
      {
        i.remove();
      }
   }
}
