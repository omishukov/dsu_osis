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


void ObsSceneSwitcher::HandleEvent(int act)
{
   Action2SceneStruct info = Action2Scene->GetActionSceneInfo(act);
   if (info.Hkey.isEmpty() || info.TransitionHkey.isEmpty())
   {
      return;
   }
   ObsAction* newAction = new ObsAction(info, CurrentAction);
   CurrentAction = newAction;
   newAction->Execute();
}

void ObsSceneSwitcher::Initialize()
{
}
