#ifndef OSISWARMUPGROUP_H
#define OSISWARMUPGROUP_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include <osisdata.h>

class OsisWarmupGroup : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisWarmupGroup(QDomElement& osisElement, QObject *parent = 0);

   inline int GetIndex() { return Ind; }

public:
   enum OsisElementAttributes
   {
      Index,
      Number // Number of participants in Warmup-Group
   };
   Q_ENUM(OsisElementAttributes)

private:
   int Ind;
};

typedef QMap <int, OsisWarmupGroup*> OsisWarmupGroupMap;

#endif // OSISWARMUPGROUP_H
