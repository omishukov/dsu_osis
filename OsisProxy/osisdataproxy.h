#ifndef OSISDATAPROXY_H
#define OSISDATAPROXY_H

#include <QObject>
#include <QDomDocument>
#include <QTcpSocket>
#include <QMutex>
#include "dataqueue.h"

class OsisDataProxy : public QObject
{
   Q_OBJECT
public:
   explicit OsisDataProxy(QObject *parent = 0);

   enum OsisXmlElements
   {
      Isu_Osis,
      // <Event_Overview>
      Event_Overview,
      Event,
      Category_List,
      Category,
      // <Segment_Start>
      Segment_Start,
      Event_Officials_List,
      Official,
      Participant_List,
      Category_Result_List,
      Segment_List,
      Participant,
      Coaches, // always empty
      Athlete_List,
      Segment,
      Criteria_List,
      Deduction_List,
      Majority_Deduction_List,
      Segment_Official_List,
      Segment_Start_List,
      Athlete,
      Criteria,
      Deduction,
      Majority_Deduction,
      Performance,
      Planned_Element_List,
      Element,
      Warmup_Group,
      // <Segment_Running>
      Segment_Running,
      Action,
      Prf_Details,
      Prf_Ranking,
      Segment_Result_List,
      Element_List,
      Prf,
      // <Segment_Statistic>
      Segment_Statistic,
   };
   Q_ENUM(OsisXmlElements)

   void SetDataIf(DataQueue* dataIf) { DataIf = dataIf; }
   void SendCache(QTcpSocket* socket);

signals:
   void Distribute(QByteArray*);

public slots:
   void ProcessData();
   void Handle(QByteArray* qba);
   void Cache(QByteArray* qba);

private:
   bool ProcessOsisTree(QDomNode& n);
   bool ProcessOsisElement(QDomNode& n);
   DataQueue* DataIf;
   bool TagFound;
   int Tag;
   QByteArray EventOverview;
   QByteArray SegmentStart;
   QByteArray PrfRanking;
   QByteArray ActionIni;
   QMutex M;

};

#endif // OSISDATAPROXY_H
