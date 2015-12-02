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
};

#endif // EVENT_H
