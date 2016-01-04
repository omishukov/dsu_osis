#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDomDocument>
#include "criteria.h"
#include "category.h"
#include "segment.h"
#include "segmentstart.h"

class OsisEvent: public QObject
{
   Q_OBJECT

public:
   OsisEvent();
   ~OsisEvent();

public:
   enum OsisEventAttributes
   {
      ID, // Identifier
      Name, //
      Abbreviation, //
      Type, // Type of the event, standard value: “T”
      CmpType, // Competition type
      ExtDt, // Results System Codes
      ODF // ???
   };
   Q_ENUM(OsisEventAttributes)

public:
   bool ProcessEvent(QDomElement& eventElement);
   bool ProcessEventAttributes(QDomElement& eventElement);
   bool ProcessCategoryList(QDomElement& categoryListElement);
   bool ProcessCategory(QDomElement& categoryElement);
   bool ProcessSegmentStart(QDomElement& e);
   bool ProcessCategoryAttributes(QDomElement& categoryElement, OsisCategory* newCategory);
   bool ProcessSegmentList(QDomElement& categoryElement);
   bool ProcessSegment(QDomElement& e);
   bool ProcessSegmentAttributes(QDomElement& segmentElement, OsisSegment* newSegment);
   bool ProcessCriteria(QDomElement& criteriaListElement);
   bool ProcessDeduction(QDomElement& deductionElement);
   bool ProcessCriteriaAttributes(QDomElement& segmentElement, OsisCriteria* newCriteria);
   bool ProcessCriteriaList(QDomElement& criteriaListElement, int SegmentId);
   bool ProcessOfficial(QDomElement& officialElement);
   bool ProcessParticipant(QDomElement& participantElement);
   bool ProcessAthlete(QDomElement& athleteElement);

   void ProcessingDone();

private:
   int event_ID;
   QString event_Name;
   QString event_Abbreviation;
   QString event_Type;
   QString event_CmpType;
   QString event_ExtDt;
   int event_ODF;

   int Current_Category;
   int Current_Segment;
   OsisSegmentStart* ActiveSegment;

   OsisCategoryMap CategoryMap;
   OsisSegmentMap SegmentMap;
};

#endif // EVENT_H
