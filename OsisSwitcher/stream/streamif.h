#ifndef STREAMIF_H
#define STREAMIF_H

#include <QObject>
#include <QStringList>
#include <QMutex>

class StreamIf
{
public:
   virtual ~StreamIf() {}

   virtual void Action(int newAction) = 0;

   virtual QStringList GetScenes() = 0;
   virtual QStringList GetSceneFiles(const QString& scene) = 0;
   virtual QStringList GetTransitions() = 0;

   virtual void SetTransition(QString& currentTransition) = 0;
   virtual void SetDataLocker(QMutex* m) = 0;

   virtual void ActionChanged(int action, int sceneIndex, QString& scene) = 0;
   virtual void ActionChanged(int action, int sceneIndex, int delay) = 0;
   virtual void ActionChanged(int action, int sceneIndex, QString& scene, int delay) = 0;

};

#endif // STREAMIF_H
