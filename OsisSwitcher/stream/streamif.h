#ifndef STREAMIF_H
#define STREAMIF_H

#include <QObject>
#include <QStringList>

class StreamIf : public QObject
{
   Q_OBJECT
public:
   virtual ~StreamIf() {}

   virtual void Action(int newAction) = 0;

   virtual QStringList GetScenes() = 0;
   virtual QStringList GetTransitions() = 0;

   virtual void SetTransition(QString currentTransition) = 0;

public slots:
   void Action(int action);
};

#endif // STREAMIF_H
