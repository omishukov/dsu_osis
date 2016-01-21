#include <osis_unittest.h>

const QByteArray data1_1("<Isu_Osis Part=\"1\" version=\"2.0\" Counter=\"1\" IsuCalcFs=\"3.1.1\" Database=\"11137\">");
const QByteArray data1_2("<Segment_Running Segment_ID=\"1\">");
const QByteArray data1_3("<Action Command=\"CLR\" Current_Participant_ID=\"390\" Current_Start_Number=\"4\" Next_Participant_ID=\"\" Prev_Participant_ID=\"47\" Next_Participant_StNum=\"5\" LastScored_Participant_StNum=\"3\"/>");
const QByteArray data1_4("</Segment_Running>");
const QByteArray data1_5("</Isu_Osis>");

const QByteArray STX("\x02");
const QByteArray ETX("\x03");
const QByteArray CRLF("\x0D\x0A");

void UnittestTest::OsisLintTestInit()
{
   osisLink = new CalcConnectionThread();
   osisDataStubIf = new OsisDataIfStub();
   osisLink->setDataIf(osisDataStubIf);
}

void UnittestTest::OsisLintTestClean()
{
   osisLink->setDataIf(0);
   delete osisLink;
   delete osisDataStubIf;
}

void UnittestTest::ReceiveStxEtx()
{
   QByteArray qbaReq;
   QByteArray qbaInd;

   OsisLintTestInit();

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
   QVERIFY2(qbaInd == osisDataStubIf->osisData, "Failure");

   osisDataStubIf->osisData.clear();

   OsisLintTestClean();
}

void UnittestTest::ReceiveStxEtxMultiple()
{
   QByteArray qbaReq;
   QByteArray qbaInd;

   OsisLintTestInit();

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
   qbaReq.clear();
   qbaReq.append(STX);
   qbaReq.append(data1_2);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.clear();
   qbaReq.append(STX);
   qbaReq.append(data1_3);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.clear();
   qbaReq.append(STX);
   qbaReq.append(data1_4);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.clear();
   qbaReq.append(STX);
   qbaReq.append(data1_5);
   qbaReq.append(CRLF);
   qbaReq.append(ETX);
   osisLink->processData(qbaReq);
   qbaReq.clear();

   QVERIFY2(qbaInd == osisDataStubIf->osisData, "Failure");

   osisDataStubIf->osisData.clear();

   OsisLintTestClean();
}
