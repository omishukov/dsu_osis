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

ObsSceneSwitcher::ObsSceneSwitcher(Actions* actions, QString obsCongigPath, QTableView* tableView, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
   , MetaActionsEnum(QMetaEnum::fromType<obs_key>())
   , OBS_Path(obsCongigPath)
   , CurrentAction(0)
   , TableView(tableView)
{
   TableGui.SetObsSwither(this);
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   SaveActions();
   for (auto obsAction : ObsActions)
   {
      delete obsAction;
   }
   ResetScenes();
   delete tableModel;
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

void ObsSceneSwitcher::SaveActions()
{
   QSettings settings(inifile, QSettings::IniFormat);

   for (auto obsAction : ObsActions)
   {
      settings.beginGroup(obsAction->actionName);
      settings.setValue("DELAY1", obsAction->GetDelay1());
      settings.setValue("SCENE1", obsAction->GetScene1Name());
      settings.setValue("DELAY2", obsAction->GetDelay2());
      settings.setValue("SCENE2", obsAction->GetScene2Name());
      settings.setValue("TRANSITION", obsAction->GetTransitionName());
      settings.endGroup();
   }
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
   //   timer->start(1000);
}

void ObsSceneSwitcher::Initialize()
{
}

void ObsSceneSwitcher::TimerEvent()
{
   qInfo() << "Timeout()";
}

