#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ObsSceneSwitcher::ObsSceneSwitcher(QString& configPath, OsisIf* osisIf, QObject *parent)
   : QObject(parent)
   , CurrentAction(0)
   , Obs(configPath)
   , OsisDataIf(osisIf)
{
   connect(this, SIGNAL(NewAction(int)), this, SLOT(HandleEvent(int)), Qt::QueuedConnection);
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   foreach (ObsAction* action, ObsActions)
   {
      delete action;
   }
}

void ObsSceneSwitcher::Action(int action)
{
   emit NewAction(action);
}

QStringList ObsSceneSwitcher::GetScenes()
{
   return Obs.GetScenes();
}

QStringList ObsSceneSwitcher::GetSceneFiles(const QString& scene)
{
   return Obs.GetSceneFiles(scene);
}

QStringList ObsSceneSwitcher::GetTransitions()
{
   return Obs.GetTransitions();
}

void ObsSceneSwitcher::SetTransition(QString& currentTransition)
{
   Obs.SetTransition(currentTransition);
}

void ObsSceneSwitcher::SetDataLocker(QMutex *m)
{
   OsisDataMutex = m;
}

void ObsSceneSwitcher::ActionChanged(int action, int sceneIndex, QString &scene)
{
   GetAction(action)->SetScene(sceneIndex, scene);
}

void ObsSceneSwitcher::ActionChanged(int action, int sceneIndex, int delay)
{
   GetAction(action)->SetDelay(sceneIndex, delay);
}

void ObsSceneSwitcher::ActionChanged(int action, int sceneIndex, QString& scene, int delay)
{
   GetAction(action)->SetScene(sceneIndex, scene);
   GetAction(action)->SetDelay(sceneIndex, delay);
}

void ObsSceneSwitcher::HandleEvent(int act)
{
   if (ObsActions.contains(act))
   {
      ObsAction *action = GetAction(act);
      if (action->Executable())
      {
         action->Execute(CurrentAction);
         CurrentAction = action;
      }
   }
}

void ObsSceneSwitcher::Initialize()
{
}

ObsAction *ObsSceneSwitcher::GetAction(int action)
{
   ObsAction *actionObject;
   if (!ObsActions.contains(action))
   {
      actionObject = new ObsAction(action, OsisDataIf);
      ObsActions[action] = actionObject;
   }
   else
   {
      actionObject = ObsActions[action];
   }
   return actionObject;
}
