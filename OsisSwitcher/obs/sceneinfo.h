#ifndef SCENEINFO_H
#define SCENEINFO_H

#include <QtCore>
#include <QObject>

class SceneInfo : public QObject
{
   Q_OBJECT
public:
   SceneInfo(QString name, QList<int> hKey, int delay, QObject *parent = 0);
   ~SceneInfo();

public slots:
   void TimerExpired();

signals:
   void ActionDone();

public:
   void SwitchScene();
   void SetTransition(SceneInfo* transition);
   void SetNextScene(SceneInfo* nextScene);
   void SetPreviousScene(SceneInfo* previousScene) { PreviousScene = previousScene; }
   void Cancel();
   bool Completed();

private:
    void SendHotkey();

private:
   QString SceneName;
   QList<int> Hotkeys;
   SceneInfo* Transition;
   SceneInfo* NextScene;
   SceneInfo* PreviousScene;
   int Delay;
   QTimer Timer;
   bool ActionCompleted;
};

#endif // SCENEINFO_H
