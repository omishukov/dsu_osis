#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ObsSceneSwitcher::ObsSceneSwitcher(QObject *parent)
   : QObject(parent)
   , CurrentAction(0)
{
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

   QMetaEnum metaEnum = QMetaEnum::fromType<OsisIf::OSIS_ACTIONS_ENUM>();
   int row = 0;
   for(int i = OsisIf::NO_ACTIONS + 1; i < OsisIf::LAST_ACTION; i++, row++)
   {
      switch (i)
      {
      case OsisIf::ACTION_1S1:
      case OsisIf::ACTION_1S2:
      case OsisIf::ACTION_1S3:
      case OsisIf::ACTION_1S4:
      case OsisIf::ACTION_1S5:
      case OsisIf::ACTION_2SC:
      case OsisIf::ACTION_3SC:
         continue; // skip these
         break;
      default:
         break;
      }
      QString ActionName = metaEnum.valueToKey(i);
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

      ObsActions.insert(i, new ObsAction(ActionName, SceneDelayMap, osisIf));
      RowActionMap.insert(row, i);
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
