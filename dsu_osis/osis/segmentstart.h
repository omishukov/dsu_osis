#ifndef OSISSEGMENTSTART_H
#define OSISSEGMENTSTART_H

#include <QObject>
#include <QDomDocument>

class OsisSegmentStart : public QObject
{
   Q_OBJECT
public:
   explicit OsisSegmentStart(QObject *parent = 0);
   OsisSegmentStart& operator=(const OsisSegmentStart &copy);

   inline int GetSegmentId() { return SS_Segment_ID; }
   inline int GetCategoryId() { return SS_Category_ID; }
   inline int GetSegmentIndex() { return SS_Segment_Index; }
   inline int GetStartingParticipant() { return SS_Starting_Participant; }
   inline int GetNextParticipant() { return SS_Next_Participant; }
   inline int GetLastFinishedParticipant() { return SS_LastFinished_Participant; }

   bool ProcessSegmentStartAttributes(QDomElement& segmentStartElement);


public:
   enum OsisSegmentStartAttributes
   {
      Segment_ID, // ID of current segment
      Category_ID, // ID of current category
      Segment_Index, // Number of current segment within current category
      Starting_Participant,
      Next_Participant,
      LastFinished_Participant
   };
   Q_ENUM(OsisSegmentStartAttributes)


signals:

public slots:

private:
   int SS_Segment_ID;
   int SS_Category_ID;
   int SS_Segment_Index;
   int SS_Starting_Participant;
   int SS_Next_Participant;
   int SS_LastFinished_Participant;
};

#endif // OSISSEGMENTSTART_H
