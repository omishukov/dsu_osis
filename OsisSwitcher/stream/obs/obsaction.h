#ifndef OBSACTION_H
#define OBSACTION_H

#include <QMetaEnum>
#include <QObject>
#include "sceneinfo.h"
#include "scenedata.h"
#include "osisif.h"

class ObsAction : public QObject
{
   Q_OBJECT
public:
//   ObsAction(Action2SceneStruct& actionInfo, ObsAction* previousAction, QObject *parent = 0);
   ObsAction(int action, OsisIf* osisIf, QObject *parent = 0);
   ~ObsAction();

public:
   void Execute(ObsAction *previousAction = 0, int nextAction = -1);
//   SceneInfo* GetScene() { return &Scene;}
//   bool Completed();
   bool Executable();

   void SetScene(int sceneIndex, QString& scene);
   void SetDelay(int sceneIndex, int delay);

public slots:
   void SceneCompleted();

private:
   typedef struct
   {
      QString Scene;
      int Delay;
   } SceneDelayStruct;
   QString ActionName;
   QMap<int, SceneDelayStruct> SceneDelayMap;
   OsisIf* OsisDataIf;
   bool Repeat;
   SceneData* ObsSceneFiles;
};

#endif // OBSACTION_H
