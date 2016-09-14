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

signals:

public slots:
   void HandleEvent(int act);
   void Initialize();

private:
   ActionToScene* osisAction;
   QMap<QString, QList<int>>* SceneHkeyMap;
   QMap<QString, QList<int>>* TransitionHkeyMap;
   ObsAction* CurrentAction;

};

#endif // OBSSCENESWITCHER_H
