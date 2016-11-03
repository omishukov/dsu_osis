#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QMetaEnum>
#include "actions.h"
#include "sceneinfo.h"
#include "scenetableui.h"
#include "actiontoscene.h"
#include "osisif.h"

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(ActionToScene* actions, QObject *parent = 0);
   ~ObsSceneSwitcher();

   void LoadActions(QString& inifile, SwitcherOsisIf* osisIf);

signals:

public slots:
   void HandleEvent(int act);
   void Initialize();

private:
   void RemoveCompletesActions();

   ActionToScene* Action2Scene;
   QMap<QString, QList<int>>* SceneHkeyMap;
   QMap<QString, QList<int>>* TransitionHkeyMap;
   ObsAction* CurrentAction;
   QList<ObsAction*> ActiveActions;
   QMap<int, ObsAction*> ObsActions;
   QString Inifile;

};

#endif // OBSSCENESWITCHER_H
