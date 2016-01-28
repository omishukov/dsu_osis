#ifndef OSISOFFICIAL_H
#define OSISOFFICIAL_H

#include <QObject>
#include <QMap>
#include "osisdata.h"

class OsisOfficial : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisOfficial(QDomElement& categoryElement, QObject *parent = 0);

   void SetSegmentId(int segmentId) { SegmentId = segmentId; }
   int GetSegmentId() { return SegmentId; }

public:
   enum OsisElementAttributes
   {
      Index, //connected to the function
      ID, //Identifier,
      Full_Name,
      Title,
      Family_Name,
      Given_Name,
      Initial, //Initial of the given name
      ScbName1, //Scoreboard name string
      Gender, // F | M
      Nation,
      Club,
      Function //OsisOfficialFunctionAttribute
   };

   enum OsisOfficialFunctionAttribute
   {
      JDG, //Judge
      ERF, //Referee
      TCO, //Technical controller
      TSP, //Technical specialist
      STS, //Assistant technical specialist
      ARI, //Assistant referee ice
      DOP, //Data operator
      ROP, //Replay operator
      REP, //ISU representative
      TDG, //Technical delegate
   };

   Q_ENUM(OsisElementAttributes)
   Q_ENUM(OsisOfficialFunctionAttribute)

private:
   int SegmentId;
};

typedef QMap <int, OsisOfficial*> OsisOfficialMap;

#endif // OSISOFFICIAL_H
