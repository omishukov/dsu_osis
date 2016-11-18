#ifndef STREAMIF_H
#define STREAMIF_H

#include <QObject>
#include <QStringList>
#include <QMutex>

class StreamIf
{
public:
   virtual ~StreamIf();

   virtual void Action(int newAction) = 0;

   virtual QStringList GetScenes() = 0;
   virtual QStringList GetTransitions() = 0;
   virtual int GetNoOfActions() = 0;
   virtual int GetNoOfSceneTransitions() = 0;

   virtual void SetTransition(QString currentTransition) = 0;
   virtual void SetDataLocker(QMutex* m) = 0;
};

#endif // STREAMIF_H
