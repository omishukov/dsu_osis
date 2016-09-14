#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern QString inifile;

ObsSceneSwitcher::ObsSceneSwitcher(ActionToScene *actions, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
   , CurrentAction(0)
{
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   for (auto obsAction : ObsActions)
   {
      delete obsAction;
   }
   ResetScenes();
}

void ObsSceneSwitcher::ResetScenes()
{
   for (auto obsScene : ObsScenesList)
   {
      delete obsScene;
   }
   ObsScenesList.clear();
   for (auto obsTransition: ObsTransitionList)
   {
      delete obsTransition;
   }
   ObsTransitionList.clear();
}


SceneInfo* ObsSceneSwitcher::GetScene(QString scene)
{
   for (auto obsScene : ObsScenesList)
   {
      if (!QString::compare(obsScene->SceneName, scene))
      {
         return obsScene;
      }
   }
   return NULL;
}

SceneInfo* ObsSceneSwitcher::GetTransition(QString transition)
{
   for (auto obsTransition : ObsTransitionList)
   {
      if (!QString::compare(obsTransition->SceneName, transition))
      {
         return obsTransition;
      }
   }
   return NULL;
}

void ObsSceneSwitcher::HandleEvent(int command)
{
   ObsAction* action = ObsActions[command];
   if (action)
   {
      qInfo() << "New action: " << action->actionName;
      action->Execute(CurrentAction);
      CurrentAction = action;
   }
}

void ObsSceneSwitcher::Initialize()
{
}

void ObsSceneSwitcher::TimerEvent()
{
   qInfo() << "Timeout()";
}

