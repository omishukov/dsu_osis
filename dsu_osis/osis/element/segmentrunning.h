#ifndef OSISSEGMENTRUNNING_H
#define OSISSEGMENTRUNNING_H

#include <QObject>
#include <QDomDocument>
#include <osisdata.h>

class OsisSegmentRunning : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisSegmentRunning(QDomElement& osisElement, QObject *parent = 0);

public:
   enum OsisElementAttributes
   {
      Segment_ID, // ID of current segment
      Category_ID, // ID of current category
      Segment_Index //Number of current segment within current category
   };
   Q_ENUM(OsisElementAttributes)
};

#endif // OSISSEGMENTRUNNING_H
