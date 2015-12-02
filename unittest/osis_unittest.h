#ifndef OSIS_UNITTEST_H
#define OSIS_UNITTEST_H
#include <QtTest>
#include "../dsu_osis/osisdataif.h"
#include "../dsu_osis/osisdataprovider.h"
#include "../dsu_osis/calcconnectionthread.h"

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

   // OsisLink
   void ReceiveStxEtx();
   void ReceiveStxEtxMultiple();

   //XmlParse
   void ParseOsisMsg();

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
   OsisDataProvider* osisDataIf;
};

#endif // OSIS_UNITTEST_H