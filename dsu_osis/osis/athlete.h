#ifndef OSISATHLETE_H
#define OSISATHLETE_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

class OsisAthlete : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisAthlete(QDomElement& osisElement, QObject *parent = 0);

   int GetId() { return Id; }

public:
   enum OsisElementAttributes
   {
      ID, //  Identifier
      Type,
      Nation,
      Full_Name, // 60
      Initial_Name, // 40 Format “Smith, D”
      Family_Name, // 30
      Given_Name, // 30
      ScbName1, // 30
      ScoreboardName1,
      ScbName2, // 30
      ScoreboardName2,
      ScbName3, // 30
      ScoreboardName3,
      ScbName4, // 30
      ScoreboardName4,
      TV_Long_Name, // 40
      TV_Short_Name, // 30
      RTDS_Long_Name, // 60
      RTDS_Short_Name, // 30
      Initial, //  Initial of given name
      Gender, // 1 M | F
      Date_Of_Birth, // 10 Format “YYYY-MM-DD”
      ExtRef, // 10  Reference ID to external database
   };

   enum OsisAthleteType
   {
      PER, // Person
      COU, // Couple
      PTS, // Team
      MIX
   };

   Q_ENUM(OsisElementAttributes)
   Q_ENUM(OsisAthleteType)


private:
   int Id;
};

typedef QMap <int, OsisAthlete*> OsisAthleteMap;

#endif // OSISATHLETE_H
