#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ObsSceneSwitcher::ObsSceneSwitcher(QString& inifile, OsisIf* osisIf, QObject *parent)
   : QObject(parent)
   , CurrentAction(0)
{
   connect(this, SIGNAL(NewAction(int)), this, SLOT(HandleEvent(int)), Qt::QueuedConnection);
   LoadActions(inifile, osisIf);
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   foreach (ObsAction* action, ObsActions)
   {
      delete action;
   }
}

QStringList ObsSceneSwitcher::GetRow(int row)
{
   if (RowActionMap.contains(row))
   {
      int action = RowActionMap[row];
      if (ObsActions.contains(action))
      {
         return ObsActions[action]->GetTableRow();
      }
   }
   return QStringList();
}

void ObsSceneSwitcher::Action(int action)
{
   emit NewAction(action);
}

QStringList ObsSceneSwitcher::GetScenes()
{

}

void ObsSceneSwitcher::HandleEvent(int act)
{
   if (ObsActions.contains(act))
   {
      ObsAction *action = ObsActions[act];
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
