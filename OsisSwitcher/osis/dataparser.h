#ifndef OSISPARSER_H
#define OSISPARSER_H

#include <QDomDocument>
#include <QObject>
#include <QMutex>
#include <QMetaEnum>
#include "dataqueue.h"
#include "competitiondata.h"
#include "obs/actions.h"

class OsisParser : public QObject
{
   Q_OBJECT
public:
   explicit OsisParser(QObject *parent = 0);

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
   void SetObsDataSaver(Actions* obsData);
   OsisIf* GetOsisIf() { return &Competition; }

signals:

public slots:
   void ProcessData();
   void Initialize();
   void Uninit();

private:
   void Handle(QByteArray& qba);
   bool ProcessOsisTree(QDomNode& n);
   bool ProcessOsisElement(QDomNode& n);

   DataQueue* DataIf;
   QMutex M;
   OsisCompetitionData Competition;
   Actions* ObsDataSaver;
};

#endif // OSISPARSER_H
