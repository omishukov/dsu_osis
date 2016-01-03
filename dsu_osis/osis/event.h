#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDomDocument>

class OsisEvent: public QObject
{
   Q_OBJECT

public:
   OsisEvent();
   ~OsisEvent();

   void AddEvent(const QDomElement &element);



public:
   enum OsisEventElements
   {
      Event
   };

   enum OsisEventAttributes
   {
      ID, // Identifier
      Name, //
      Abbreviation, //
      Type, // Type of the event, standard value: “T”
      CmpType, // Competition type
      ExtDt, // Results System Codes
   };

   Q_ENUM(OsisEventElements)
   Q_ENUM(OsisEventAttributes)

private:
   int event_ID;
   QString event_Name;
   QString event_Abbreviation;
   QString event_Type;
   QString event_CmpType;
   QString event_ExtDt;
};

#endif // EVENT_H
