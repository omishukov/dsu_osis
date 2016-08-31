#ifndef SCENEINFO_H
#define SCENEINFO_H

#include <QObject>

class SceneInfo
{
public:
   SceneInfo(QString name, QList<int> list);

   void SwitchScene();

private:
   QString SceneName;
   QList<int> Hotkeys;
};

#endif // SCENEINFO_H
