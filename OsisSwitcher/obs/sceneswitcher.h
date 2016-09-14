#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QMetaEnum>
#include "actions.h"
#include "sceneinfo.h"
#include "scenetableui.h"

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(ActionToScene* actions, QObject *parent = 0);
   ~ObsSceneSwitcher();

   SceneInfo* GetScene(QString scene);
   SceneInfo* GetTransition(QString transition);

signals:

public slots:
   void HandleEvent(int command);
   void Initialize();
   void TimerEvent();

private:
   ActionToScene* osisAction;
   QMap<int, ObsAction*> ObsActions;
public:
   QList<SceneInfo*> ObsScenesList;
   QList<SceneInfo*> ObsTransitionList;
private:
   void ResetScenes();
   SceneTableUi TableGui;
   ObsAction* CurrentAction;
};

#endif // OBSSCENESWITCHER_H
