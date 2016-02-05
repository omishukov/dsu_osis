#ifndef OSISPERFORMANCE_H
#define OSISPERFORMANCE_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include <osisdata.h>
#include <element/element.h>

class OsisPerformance : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisPerformance(QDomElement& osisElement, QObject *parent = 0);

   inline int GetId() { return Id; }
   void AddElement(OsisElement* newElement);

public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Start_Number,
      Start_Group_Number,
      PElmScore, //Planned element score
      Personal_Best, //Personal best in segment
      Personal_Best_Tot, //Total personal best
      Season_Best, //Season best in segment
      Season_Best_Tot, //Total season best
      Season_Best_Rank,
      Season_Best_Index,
      Season_Best_Tot_Rank,
      Season_Best_Tot_Index,
      Status, //Performance status
      Points, //Format “9.99”
      TES, //Technical element score
      TCS, //Program component score
      Bonus,
      Ded_Sum, //Sum of the deductions, Format “9.99”
      Qualified, //“Q” when qualified
      Points_Needed1, //Required points to get into 1st position
      Points_Needed2, //Required points to get into 2nd position
      Points_Needed3, //Required points to get into 3rd position
      StartTime,
      Prf_ID
   };

   enum OsisPerformanceStatus
   {
      REM, //Remaining
      OK, //Ok, skater received result, which is valid for ranking
      IRM, //Invalid result mark (withdrawn, disqualified)
      NIS //Not in segment
   };
   Q_ENUM(OsisElementAttributes)
   Q_ENUM(OsisPerformanceStatus)

private:
   int Id;
   OsisElementMap Elements;
};

typedef QMap <int, OsisPerformance*> OsisPerformanceMap;

#endif // OSISPERFORMANCE_H
