#include <QString>
#include <QtTest>
#include "../dsu_osis/osisdataif.h"
#include "../dsu_osis/calcconnectionthread.h"

const QByteArray data1_1("<Isu_Osis Part=\"1\" version=\"2.0\" Counter=\"1\" IsuCalcFs=\"3.1.1\" Database=\"11137\">");
const QByteArray data1_2("<Segment_Running Segment_ID=\"1\">");
const QByteArray data1_3("<Action Command=\"CLR\" Current_Participant_ID=\"390\" Current_Start_Number=\"4\" Next_Participant_ID=\"\" Prev_Participant_ID=\"47\" Next_Participant_StNum=\"5\" LastScored_Participant_StNum=\"3\"/>");
const QByteArray data1_4("</Segment_Running>");
const QByteArray data1_5("</Isu_Osis>");

const QByteArray STX("\x02");
const QByteArray ETX("\x03");
const QByteArray CRLF("\x0D\x0A");


class OsisDataIfStub: public OsisDataIf
{
public:
   virtual ~OsisDataIfStub() {osisData.clear();}
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
   void testCase1();
   void testCase2();

private:
   CalcConnectionThread* osisLink;
   OsisDataIfStub* osisDataIf;
};

UnittestTest::UnittestTest()
{
   osisLink = 0;
   osisDataIf = 0;
}

void UnittestTest::initTestCase()
{
   osisLink = new CalcConnectionThread();
   osisDataIf = new OsisDataIfStub();
   osisLink->setDataIf(osisDataIf);
   osisDataIf->osisData.clear();
}

void UnittestTest::cleanupTestCase()
{
   osisLink->setDataIf(0);
   delete osisLink;
   delete osisDataIf;
}

void UnittestTest::testCase1()
{
   QByteArray qbaReq;
   QByteArray qbaInd;
   qbaInd.append(data1_1);
   qbaInd.append(data1_2);
   qbaInd.append(data1_3);
   qbaInd.append(data1_4);
   qbaInd.append(data1_5);
   qbaInd.append(CRLF);

   qbaReq.append(STX);
   qbaReq.append(qbaInd);
   qbaReq.append(ETX);

   osisLink->processData(qbaReq);
   QVERIFY2(qbaInd == osisDataIf->osisData, "Failure");

   osisDataIf->osisData.clear();
}

void UnittestTest::testCase2()
{
   QByteArray qbaReq;
   QByteArray qbaInd;
   qbaInd.append(data1_1);
   qbaInd.append(data1_2);
   qbaInd.append(data1_3);
   qbaInd.append(data1_4);
   qbaInd.append(data1_5);
   qbaInd.append(CRLF);

   qbaReq.append(STX);
   qbaReq.append(data1_1);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.append(STX);
   qbaReq.append(data1_2);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.append(STX);
   qbaReq.append(data1_3);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.append(STX);
   qbaReq.append(data1_4);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.append(STX);
   qbaReq.append(data1_5);
   qbaReq.append(CRLF);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);

   QVERIFY2(qbaInd == osisDataIf->osisData, "Failure");

   osisDataIf->osisData.clear();
}

QTEST_APPLESS_MAIN(UnittestTest)

#include "tst_unittesttest.moc"