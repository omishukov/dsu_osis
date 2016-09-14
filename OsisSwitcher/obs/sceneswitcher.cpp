#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ObsSceneSwitcher::ObsSceneSwitcher(ActionToScene *actions, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
   , CurrentAction(0)
{

}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
}


void ObsSceneSwitcher::HandleEvent(int act)
{
   if (osisAction[act].Hkey.isEmpty() || osisAction[act].TransitionHkey.isEmpty())
   {
      return;
   }
   ObsAction* newAction = new ObsAction(&osisAction[act], CurrentAction);
   CurrentAction = newAction;
   newAction->Execute();
}

void ObsSceneSwitcher::Initialize()
{
}
