#ifndef STREAMIF_H
#define STREAMIF_H

#include <QStringList>

class StreamIf
{
public:
   virtual ~StreamIf() {}

   virtual void Action(int newAction) = 0;

   virtual QStringList GetScenes() = 0;
   virtual QStringList GetTransitions() = 0;

   virtual void SetTransition(QString currentTransition) = 0;

};

#endif // STREAMIF_H
