#ifndef SCENEINFO_H
#define SCENEINFO_H

#include <QObject>

class SceneInfo
{
public:
   SceneInfo(QString name, QList<int> list);

   void SwitchScene();
   void SetTransition(SceneInfo* transition) { Transition = transition; }

   QString SceneName;
private:
   QList<int> Hotkeys;
   SceneInfo* Transition;
   SceneInfo* NextScene;
};

#endif // SCENEINFO_H
