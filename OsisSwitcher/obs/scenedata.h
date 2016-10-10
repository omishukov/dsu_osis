#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <QObject>

class SceneData : public QObject
{
   Q_OBJECT
public:
   explicit SceneData(QObject *parent = 0);

signals:

public slots:
};

#endif // SCENEDATA_H