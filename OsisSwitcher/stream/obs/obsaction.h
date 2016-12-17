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
   ObsAction(int action, OsisIf* osisIf, QObject *parent = 0);
   ~ObsAction();

public:
   void Execute(ObsAction *previousAction = 0, int nextAction = -1);
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
   int ActionIndex;
   QMap<int, SceneDelayStruct> SceneDelayMap;
   QMap<int, SceneDelayStruct>::const_iterator iSDMap;
   OsisIf* OsisDataIf;
   bool Repeat;
   SceneData* ObsSceneFiles;
   bool Active;
};

#endif // OBSACTION_H
