#ifndef SCENEINFO_H
#define SCENEINFO_H

#include <QtCore>
#include <QObject>

class SceneInfo : public QObject
{
   Q_OBJECT
public:
   SceneInfo(QString name, QList<int> list, QObject *parent = 0);
   ~SceneInfo();

public slots:
   void TimerExpired();

public:
   void SwitchScene(SceneInfo *previousScene = 0);

   void SetTransition(SceneInfo* transition);
   SceneInfo* GetTransition() { return Transition; }

   void SetNextScene(SceneInfo* nextScene);
   SceneInfo* GetNextScene() { return NextScene; }

   void SetDelay(int delay) { Delay = delay; }
   int GetDelay() { return Delay; }

   void Cancel();

   QString SceneName;
   QList<int> Hotkeys;

//protected:
//    void timerEvent(QTimerEvent *event);

private:
    void SendHotkey();

private:
   SceneInfo* Transition;
   SceneInfo* NextScene;
   SceneInfo* PreviousScene;
   int Delay;
   QTimer *timer;
};

#endif // SCENEINFO_H
