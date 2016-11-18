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

void ObsSceneSwitcher::LoadActions(QString& inifile, OsisIf* osisIf)
{
   Inifile = inifile;
   QSettings settings(Inifile, QSettings::IniFormat);
   QString sceneName;
   int sceneDelay;

   const QMap<int, QString>* actionList = osisIf->GetActions();
   QMapIterator<int, QString> i(*actionList);
   int row = 0;
   while (i.hasNext())
   {
      i.next();
      QString ActionName = i.value();
      QMap<QString, int> SceneDelayMap;

      settings.beginGroup(ActionName);
      for (int sc = 0; sc < NUM_SCENES_PER_ACTION; sc++)
      {
         QString Scene = QString("SCENE%s").arg(sc + 1);
         QString Delay = QString("DELAY%s").arg(sc + 1);
         sceneName = settings.value(Scene, "").toString();
         sceneDelay = settings.value(Delay, "0").toInt();
         SceneDelayMap.insert(sceneName, sceneDelay);
      }
      settings.endGroup();

      ObsActions.insert(i.key(), new ObsAction(ActionName, SceneDelayMap, osisIf));
Move it to ConfigUI:      RowActionMap.insert(row++, i.key());
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
