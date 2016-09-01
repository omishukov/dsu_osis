#ifndef OSIS_UNITTEST_H
#define OSIS_UNITTEST_H
#include <QtTest>
#include "../dsu_osis/osis/osisxml.h"
#include "../dsu_osis/calcconnectionthread.h"
#include "../dsu_osis/isucompetition.h"
#include "../dsu_osis/obs/sceneswitcher.h"

class OsisDataIfStub: public OsisDataIf
{
public:
   virtual ~OsisDataIfStub() { osisData.clear(); }
   virtual void DataInd(class QByteArray& qba) { osisData.append(qba);}

public:
   QByteArray osisData;
};

class UnittestTest : public QObject
{
   Q_OBJECT

public:
   UnittestTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void RecursiveTest();

   // OsisLink
   void ReceiveStxEtx();
   void ReceiveStxEtxMultiple();

   //XmlParse
   void ParseOsisEventOverview();
   void ParseOsisSegmentStart();
   void ParseOsisAction();
   void ParseOsisAll();
   void ObsTransition();
   void ObsParseTransitionIni();
   void ObsTimer();

private:
   // OsisLink Helpers
   void OsisLintTestInit();
   void OsisLintTestClean();
   OsisDataIfStub* osisDataStubIf;

   // OsisXml Helpers
   void OsisXmlTestInit();
   void OsisXmlTestClean();
   bool GetXmlData(QByteArray& qba, const QString &filename);

   CalcConnectionThread* osisLink;
   OsisXml* osisDataIf;
   IsuCompetition* competition;
};

#endif // OSIS_UNITTEST_H
