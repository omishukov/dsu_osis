#include <osis_unittest.h>

const QByteArray data1_1("<Isu_Osis Part=\"1\" version=\"2.0\" Counter=\"1\" IsuCalcFs=\"3.1.1\" Database=\"11137\">");
const QByteArray data1_2("<Segment_Running Segment_ID=\"1\">");
const QByteArray data1_3("<Action Command=\"CLR\" Current_Participant_ID=\"390\" Current_Start_Number=\"4\" Next_Participant_ID=\"\" Prev_Participant_ID=\"47\" Next_Participant_StNum=\"5\" LastScored_Participant_StNum=\"3\"/>");
const QByteArray data1_4("</Segment_Running>");
const QByteArray data1_5("</Isu_Osis>");

const QByteArray data2("\x02<Isu_Osis Part=\"1\" version=\"2.0\" Counter=\"1\" IsuCalcFs=\"3.2.5\" Database=\"11142\"><Segment_Start Category_ID=\"1\" Segment_ID=\"1\" Segment_Index=\"1\" Starting_Participant=\"1\" Next_Participant=\"2\" LastFinished_Participant=\"0\"><Event ID=\"1\" Name=\"Test Event\" Abbreviation=\"TEEV\" Type=\"T\" CmpType=\"Y\" ODF=\"0\" ExtDt=\"\"><Event_Officials_List/><Category_List><Category ID=\"1\" Name=\"Men\" Level=\"SEN\" Gender=\"M\" Type=\"SGL\" tec_id=\"0\" ExtDt=\"\" TypeName=\"Men\"><Participant_List><Participant ID=\"36\" Status=\"ACT\" Type=\"PER\" Full_Name=\"Alexander ABT\" Short_Name=\"Alexander ABT\" TV_Long_Name=\"Alexander ABT\" TV_Short_Name=\"Alexander ABT\" ScbName1=\"Alexander ABT\" ScbName2=\"Alexander ABT\" ScbName3=\"Alexander ABT\" ScbName4=\"Alexander ABT\" Gender=\"M\" Nation=\"RUS\" Club=\"\" Music=\"Yablochko by R. Gliere\" Coach=\"Alexander Zhulin\" ExtRef=\"1916\" RegNum=\"\" TeamName=\"\" TeamNation=\"\" Status_Changed=\"0\" Organisation=\"\"><Athlete_List><Athlete ID=\"36\" Type=\"PER\" Nation=\"RUS\" Full_Name=\"Alexander ABT\" Initial_Name=\"ABT, A.\" Family_Name=\"ABT\" Given_Name=\"Alexander\" Printed_Long_Name=\"Alexander ABT\" Printed_Short_Name=\"Alexander ABT\" Initial=\"A.\" ScbName1=\"Alexander ABT\" ScbName2=\"Alexander ABT\" ScbName3=\"Alexander ABT\" ScbName4=\"Alexander ABT\" TV_Long_Name=\"Alexander ABT\" TV_Short_Name=\"Alexander ABT\" RTDS_Long_Name=\"\" RTDS_Short_Name=\"\" Gender=\"M\" Date_Of_Birth=\"1976-10-22\" ExtRef=\"1916\" RegNum=\"\" Organisation=\"\"/></Athlete_List></Participant><Participant ID=\"18\" Status=\"ACT\" Type=\"PER\" Full_Name=\"Ben FERREIRA\" Short_Name=\"Ben FERREIRA\" TV_Long_Name=\"Ben FERREIRA\" TV_Short_Name=\"Ben FERREIRA\" ScbName1=\"Ben FERREIRA\" ScbName2=\"Ben FERREIRA\" ScbName3=\"Ben FERREIRA\" ScbName4=\"Ben FERREIRA\" Gender=\"M\" Nation=\"CAN\" Club=\"\" Music=\"Oh' But on the Third Day\" Coach=\"Douglas Leigh, Michelle Leigh\" ExtRef=\"90272\" RegNum=\"\" TeamName=\"\" TeamNation=\"\" Status_Changed=\"0\" Organisation=\"\"><Athlete_List><Athlete ID=\"18\" Type=\"PER\" Nation=\"CAN\" Full_Name=\"Ben FERREIRA\" Initial_Name=\"FERREIRA, B.\" Family_Name=\"FERREIRA\" Given_Name=\"Ben\" Printed_Long_Name=\"Ben FERREIRA\" Printed_Short_Name=\"Ben FERREIRA\" Initial=\"B.\" ScbName1=\"Ben FERREIRA\" ScbName2=\"Ben FERREIRA\" ScbName3=\"Ben FERREIRA\" ScbName4=\"Ben FERREIRA\" TV_Long_Name=\"Ben FERREIRA\" TV_Short_Name=\"Ben FERREIRA\" RTDS_Long_Name=\"\" RTDS_Short_Name=\"\" Gender=\"M\" Date_Of_Birth=\"1979-04-05\" ExtRef=\"90272\" RegNum=\"\" Organisation=\"\"/></Athlete_List></Participant><Participant ID=\"33\" Status=\"ACT\" Type=\"PER\" Full_Name=\"Takeshi HONDA\" Short_Name=\"Takeshi HONDA\" TV_Long_Name=\"Takeshi HONDA\" TV_Short_Name=\"Takeshi HONDA\" ScbName1=\"Takeshi HONDA\" ScbName2=\"Takeshi HONDA\" ScbName3=\"Takeshi HONDA\" ScbName4=\"Takeshi HONDA\" Gender=\"M\" Nation=\"JPN\" Club=\"\" Music=\"Romeo and Juliet by N. Rota\" Coach=\"Douglas Leigh, Michelle Leigh\" ExtRef=\"90068\" RegNum=\"\" TeamName=\"\" TeamNation=\"\" Status_Changed=\"0\" Organisation=\"\"><Athlete_List><Athlete ID=\"33\" Type=\"PER\" Nation=\"JPN\" Full_Name=\"Takeshi HONDA\" Initial_Name=\"HONDA, T.\" Family_Name=\"HONDA\" Given_Name=\"Takeshi\" Printed_Long_Name=\"Takeshi HONDA\" Printed_Short_Name=\"Takeshi HONDA\" Initial=\"T.\" ScbName1=\"Takeshi HONDA\" ScbName2=\"Takeshi HONDA\" ScbName3=\"Takeshi HONDA\" ScbName4=\"Takeshi HONDA\" TV_Long_Name=\"Takeshi HONDA\" TV_Short_Name=\"Takeshi HONDA\" RTDS_Long_Name=\"\" RTDS_Short_Name=\"\" Gender=\"M\" Date_Of_Birth=\"1981-03-23\" ExtRef=\"90068\" RegNum=\"\" Organisation=\"\"/></Athlete_List></Participant><Participant ID=\"47\" Status=\"ACT\" Type=\"PER\" Full_Name=\"Michael WEISS\" Short_Name=\"Michael WEISS\" TV_Long_Name=\"Michael WEISS\" TV_Short_Name=\"Michael WEISS\" ScbName1=\"Michael WEISS\" ScbName2=\"Michael WEISS\" ScbName3=\"Michael WEISS\" ScbName4=\"Michael WEISS\" Gender=\"M\" Nation=\"USA\" Club=\"\" Music=\"Henry V  by Patrick Doyle\" Coach=\"Don Laws, Lisa Thornton Weiss\" ExtRef=\"90129\" RegNum=\"\" TeamName=\"\" TeamNation=\"\" Status_Changed=\"0\" Organisation=\"\"><Athlete_List><Athlete ID=\"47\" Type=\"PER\" Nation=\"USA\" Full_Name=\"Michael WEISS\" Initial_Name=\"WEISS, M.\" Family_Name=\"WEISS\" Given_Name=\"Michael\" Printed_Long_Name=\"Michael WEISS\" Printed_Short_Name=\"Michael WEISS\" Initial=\"M.\" ScbName1=\"Michael WEISS\" ScbName2=\"Michael WEISS\" ScbName3=\"Michael WEISS\" ScbName4=\"Michael WEISS\" TV_Long_Name=\"Michael WEISS\" TV_Short_Name=\"Michael WEISS\" RTDS_Long_Name=\"\" RTDS_Short_Name=\"\" Gender=\"M\" Date_Of_Birth=\"1976-08-02\" ExtRef=\"90129\" RegNum=\"\" Organisation=\"\"/></Athlete_List></Participant><Participant ID=\"390\" Status=\"ACT\" Type=\"PER\" Full_Name=\"Stefan LINDEMANN\" Short_Name=\"Stefan LINDEMANN\" TV_Long_Name=\"Stefan LINDEMANN\" TV_Short_Name=\"Stefan LINDEMANN\" ScbName1=\"Stefan LINDEMANN\" ScbName2=\"Stefan LINDEMANN\" ScbName3=\"Stefan LINDEMANN\" ScbName4=\"Stefan LINDEMANN\" Gender=\"M\" Nation=\"GER\" Club=\"\" Music=\"Earnest (soundtrack)\" Coach=\"Ilona Schindler\" ExtRef=\"\" RegNum=\"\" TeamName=\"\" TeamNation=\"\" Status_Changed=\"0\" Organisation=\"\"><Athlete_List><Athlete ID=\"390\" Type=\"PER\" Nation=\"GER\" Full_Name=\"Stefan LINDEMANN\" Initial_Name=\"LINDEMANN, S.\" Family_Name=\"LINDEMANN\" Given_Name=\"Stefan\" Printed_Long_Name=\"Stefan LINDEMANN\" Printed_Short_Name=\"Stefan LINDEMANN\" Initial=\"S.\" ScbName1=\"Stefan LINDEMANN\" ScbName2=\"Stefan LINDEMANN\" ScbName3=\"Stefan LINDEMANN\" ScbName4=\"Stefan LINDEMANN\" TV_Long_Name=\"Stefan LINDEMANN\" TV_Short_Name=\"Stefan LINDEMANN\" RTDS_Long_Name=\"\" RTDS_Short_Name=\"\" Gender=\"M\" Date_Of_Birth=\"1980-09-30\" ExtRef=\"\" RegNum=\"\" Organisation=\"\"/></Athlete_List></Participant></Participant_List><Category_Result_List><Participant ID=\"18\" Index=\"1\" TIndex=\"1\" TRank=\"0\" TPoint=\"0.00\" Status=\"ACT\" Segment1_Status=\"L\" Segment1_Rank=\"\" Segment1_Index=\"\" Segment1_Points=\"\" Segment1_IIndex=\"\" Segment1_IRank=\"\" Segment2_Status=\"L\" Segment2_Rank=\"\" Segment2_Index=\"\" Segment2_Points=\"\" Segment2_IIndex=\"\" Segment2_IRank=\"\" Segment3_Status=\" \" Segment3_Rank=\"\" Segment3_Index=\"\" Segment3_Points=\"\" Segment3_IIndex=\"\" Segment3_IRank=\"\" Segment4_Status=\" \" Segment4_Rank=\"\" Segment4_Index=\"\" Segment4_Points=\"\" Segment4_IIndex=\"\" Segment4_IRank=\"\" Segment5_Status=\" \" Segment5_Rank=\"\" Segment5_Index=\"\" Segment5_Points=\"\" Segment5_IIndex=\"\" Segment5_IRank=\"\" Segment6_Status=\" \" Segment6_Rank=\"\" Segment6_Index=\"\" Segment6_Points=\"\" Segment6_IIndex=\"\" Segment6_IRank=\"\"/><Participant ID=\"390\" Index=\"2\" TIndex=\"2\" TRank=\"0\" TPoint=\"0.00\" Status=\"ACT\" Segment1_Status=\"L\" Segment1_Rank=\"\" Segment1_Index=\"\" Segment1_Points=\"\" Segment1_IIndex=\"\" Segment1_IRank=\"\" Segment2_Status=\"L\" Segment2_Rank=\"\" Segment2_Index=\"\" Segment2_Points=\"\" Segment2_IIndex=\"\" Segment2_IRank=\"\" Segment3_Status=\" \" Segment3_Rank=\"\" Segment3_Index=\"\" Segment3_Points=\"\" Segment3_IIndex=\"\" Segment3_IRank=\"\" Segment4_Status=\" \" Segment4_Rank=\"\" Segment4_Index=\"\" Segment4_Points=\"\" Segment4_IIndex=\"\" Segment4_IRank=\"\" Segment5_Status=\" \" Segment5_Rank=\"\" Segment5_Index=\"\" Segment5_Points=\"\" Segment5_IIndex=\"\" Segment5_IRank=\"\" Segment6_Status=\" \" Segment6_Rank=\"\" Segment6_Index=\"\" Segment6_Points=\"\" Segment6_IIndex=\"\" Segment6_IRank=\"\"/><Participant ID=\"33\" Index=\"3\" TIndex=\"3\" TRank=\"0\" TPoint=\"0.00\" Status=\"ACT\" Segment1_Status=\"L\" Segment1_Rank=\"\" Segment1_Index=\"\" Segment1_Points=\"\" Segment1_IIndex=\"\" Segment1_IRank=\"\" Segment2_Status=\"L\" Segment2_Rank=\"\" Segment2_Index=\"\" Segment2_Points=\"\" Segment2_IIndex=\"\" Segment2_IRank=\"\" Segment3_Status=\" \" Segment3_Rank=\"\" Segment3_Index=\"\" Segment3_Points=\"\" Segment3_IIndex=\"\" Segment3_IRank=\"\" Segment4_Status=\" \" Segment4_Rank=\"\" Segment4_Index=\"\" Segment4_Points=\"\" Segment4_IIndex=\"\" Segment4_IRank=\"\" Segment5_Status=\" \" Segment5_Rank=\"\" Segment5_Index=\"\" Segment5_Points=\"\" Segment5_IIndex=\"\" Segment5_IRank=\"\" Segment6_Status=\" \" Segment6_Rank=\"\" Segment6_Index=\"\" Segment6_Points=\"\" Segment6_IIndex=\"\" Segment6_IRank=\"\"/><Participant ID=\"36\" Index=\"4\" TIndex=\"4\" TRank=\"0\" TPoint=\"0.00\" Status=\"ACT\" Segment1_Status=\"L\" Segment1_Rank=\"\" Segment1_Index=\"\" Segment1_Points=\"\" Segment1_IIndex=\"\" Segment1_IRank=\"\" Segment2_Status=\"L\" Segment2_Rank=\"\" Segment2_Index=\"\" Segment2_Points=\"\" Segment2_IIndex=\"\" Segment2_IRank=\"\" Segment3_Status=\" \" Segment3_Rank=\"\" Segment3_Index=\"\" Segment3_Points=\"\" Segment3_IIndex=\"\" Segment3_IRank=\"\" Segment4_Status=\" \" Segment4_Rank=\"\" Segment4_Index=\"\" Segment4_Points=\"\" Segment4_IIndex=\"\" Segment4_IRank=\"\" Segment5_Status=\" \" Segment5_Rank=\"\" Segment5_Index=\"\" Segment5_Points=\"\" Segment5_IIndex=\"\" Segment5_IRank=\"\" Segment6_Status=\" \" Segment6_Rank=\"\" Segment6_Index=\"\" Segment6_Points=\"\" Segment6_IIndex=\"\" Segment6_IRank=\"\"/><Participant ID=\"47\" Index=\"5\" TIndex=\"5\" TRank=\"0\" TPoint=\"0.00\" Status=\"ACT\" Segment1_Status=\"L\" Segment1_Rank=\"\" Segment1_Index=\"\" Segment1_Points=\"\" Segment1_IIndex=\"\" Segment1_IRank=\"\" Segment2_Status=\"L\" Segment2_Rank=\"\" Segment2_Index=\"\" Segment2_Points=\"\" Segment2_IIndex=\"\" Segment2_IRank=\"\" Segment3_Status=\" \" Segment3_Rank=\"\" Segment3_Index=\"\" Segment3_Points=\"\" Segment3_IIndex=\"\" Segment3_IRank=\"\" Segment4_Status=\" \" Segment4_Rank=\"\" Segment4_Index=\"\" Segment4_Points=\"\" Segment4_IIndex=\"\" Segment4_IRank=\"\" Segment5_Status=\" \" Segment5_Rank=\"\" Segment5_Index=\"\" Segment5_Points=\"\" Segment5_IIndex=\"\" Segment5_IRank=\"\" Segment6_Status=\" \" Segment6_Rank=\"\" Segment6_Index=\"\" Segment6_Points=\"\" Segment6_IIndex=\"\" Segment6_IRank=\"\"/></Category_Result_List><Segment_List><Segment ID=\"1\" Name=\"Short Program\" Abbreviation=\"SP\" Name_Of_Dance=\"\" Type=\"S\" Number_Of_Judges=\"10\" Number_Of_Decisive_Judges=\"10\" Group=\"\" QCrit=\" \" QNumber=\"0\" ExtDt=\"\" Medal=\"0\"><Criteria_List><Criteria Index=\"1\" Cri_Name=\"Skating Skills\" Cri_Abbrev=\"SS\" Cri_Factor=\"1.00\"/><Criteria Index=\"2\" Cri_Name=\"Transitions\" Cri_Abbrev=\"TR\" Cri_Factor=\"1.00\"/><Criteria Index=\"3\" Cri_Name=\"Performance\" Cri_Abbrev=\"PE\" Cri_Factor=\"1.00\"/><Criteria Index=\"4\" Cri_Name=\"Composition\" Cri_Abbrev=\"CO\" Cri_Factor=\"1.00\"/><Criteria Index=\"5\" Cri_Name=\"Interpretation of the Music\" Cri_Abbrev=\"IN\" Cri_Factor=\"1.00\"/></Criteria_List><Deduction_List><Deduction Index=\"1\" Ded_Name=\"Costume/Prop violation\" Ded_Edit=\"D\"/><Deduction Index=\"2\" Ded_Name=\"Time violation\" Ded_Edit=\"C\"/><Deduction Index=\"4\" Ded_Name=\"Illegal element/movement\" Ded_Edit=\"B\"/><Deduction Index=\"5\" Ded_Name=\"Falls\" Ded_Edit=\"B\"/><Deduction Index=\"6\" Ded_Name=\"Interruption in excess\" Ded_Edit=\"C\"/><Deduction Index=\"10\" Ded_Name=\"Costume failure\" Ded_Edit=\"C\"/><Deduction Index=\"11\" Ded_Name=\"Late start\" Ded_Edit=\"C\"/></Deduction_List><Majority_Deduction_List><Majority_Deduction Index=\"1\" Ded_Index=\"1\"/></Majority_Deduction_List><Segment_Official_List><Official Index=\"1\" ID=\"690\" Full_Name=\"Ms. Jodi ABBOTT\" Title=\"Ms.\" Family_Name=\"ABBOTT\" Given_Name=\"Jodi\" Initial=\"J.\" ScbName1=\"Jodi ABBOTT\" ScbName4=\"Jodi ABBOTT\" Gender=\"F\" Nation=\"CAN\" Club=\"\" Function=\"JDG\"/><Official Index=\"2\" ID=\"197\" Full_Name=\"Mr. Yury BALKOV\" Title=\"Mr.\" Family_Name=\"BALKOV\" Given_Name=\"Yury\" Initial=\"Y.\" ScbName1=\"Yury BALKOV\" ScbName4=\"Yury BALKOV\" Gender=\"M\" Nation=\"UKR\" Club=\"\" Function=\"JDG\"/><Official Index=\"3\" ID=\"892\" Full_Name=\"Ms. Breda MARINSEK\" Title=\"Ms.\" Family_Name=\"MARINSEK\" Given_Name=\"Breda\" Initial=\"B.\" ScbName1=\"Breda MARINSEK\" ScbName4=\"Breda MARINSEK\" Gender=\"F\" Nation=\"SLO\" Club=\"\" Function=\"JDG\"/><Official Index=\"4\" ID=\"1058\" Full_Name=\"Ms. Inger ANDERSSON\" Title=\"Ms.\" Family_Name=\"ANDERSSON\" Given_Name=\"Inger\" Initial=\"I.\" ScbName1=\"Inger ANDERSSON\" ScbName4=\"Inger ANDERSSON\" Gender=\"F\" Nation=\"SWE\" Club=\"\" Function=\"JDG\"/><Official Index=\"5\" ID=\"9\" Full_Name=\"Mr. Hideo SUGITA\" Title=\"Mr.\" Family_Name=\"SUGITA\" Given_Name=\"Hideo\" Initial=\"H.\" ScbName1=\"Hideo SUGITA\" ScbName4=\"Hideo SUGITA\" Gender=\"M\" Nation=\"JPN\" Club=\"\" Function=\"JDG\"/><Official Index=\"6\" ID=\"200\" Full_Name=\"Ms. Irina NECHKINA\" Title=\"Ms.\" Family_Name=\"NECHKINA\" Given_Name=\"Irina\" Initial=\"I.\" ScbName1=\"Irina NECHKINA\" ScbName4=\"Irina NECHKINA\" Gender=\"F\" Nation=\"AZE\" Club=\"\" Function=\"JDG\"/><Official Index=\"7\" ID=\"416\" Full_Name=\"Mr. Alexander PENCHEV\" Title=\"Mr.\" Family_Name=\"PENCHEV\" Given_Name=\"Alexander\" Initial=\"A.\" ScbName1=\"Alexander PENCHEV\" ScbName4=\"A. PENCHEV\" Gender=\"M\" Nation=\"BUL\" Club=\"\" Function=\"JDG\"/><Official Index=\"8\" ID=\"603\" Full_Name=\"Ms. Leena POHJANNE\" Title=\"Ms.\" Family_Name=\"POHJANNE\" Given_Name=\"Leena\" Initial=\"L.\" ScbName1=\"Leena POHJANNE\" ScbName4=\"Leena POHJANNE\" Gender=\"F\" Nation=\"FIN\" Club=\"\" Function=\"JDG\"/><Official Index=\"9\" ID=\"1070\" Full_Name=\"Mr. Roland MADER\" Title=\"Mr.\" Family_Name=\"MADER\" Given_Name=\"Roland\" Initial=\"R.\" ScbName1=\"Roland MADER\" ScbName4=\"Roland MADER\" Gender=\"M\" Nation=\"SUI\" Club=\"\" Function=\"JDG\"/><Official Index=\"10\" ID=\"199\" Full_Name=\"Ms. Monika ZEIDLER\" Title=\"Ms.\" Family_Name=\"ZEIDLER\" Given_Name=\"Monika\" Initial=\"M.\" ScbName1=\"Monika ZEIDLER\" ScbName4=\"Monika ZEIDLER\" Gender=\"F\" Nation=\"GER\" Club=\"\" Function=\"JDG\"/><Official Index=\"16\" ID=\"10\" Full_Name=\"Ms. Felicitas BABUSIKOVA\" Title=\"Ms.\" Family_Name=\"BABUSIKOVA\" Given_Name=\"Felicitas\" Initial=\"F.\" ScbName1=\"Felicitas BABUSIKOVA\" ScbName4=\"F. BABUSIKOVA\" Gender=\"F\" Nation=\"ISU\" Club=\"\" Function=\"ERF\"/><Official Index=\"17\" ID=\"124\" Full_Name=\"Mr. Vladislav PETUKHOV\" Title=\"Mr.\" Family_Name=\"PETUKHOV\" Given_Name=\"Vladislav\" Initial=\"V.\" ScbName1=\"Vladislav PETUKHOV\" ScbName4=\"V. PETUKHOV\" Gender=\"M\" Nation=\"ISU\" Club=\"\" Function=\"TCO\"/><Official Index=\"18\" ID=\"683\" Full_Name=\"Mr. Alexei URMANOV\" Title=\"Mr.\" Family_Name=\"URMANOV\" Given_Name=\"Alexei\" Initial=\"A.\" ScbName1=\"Alexei URMANOV\" ScbName4=\"Alexei URMANOV\" Gender=\"M\" Nation=\"ISU\" Club=\"\" Function=\"TSP\"/><Official Index=\"19\" ID=\"685\" Full_Name=\"Mr. Ricardo OLAVARRIETA\" Title=\"Mr.\" Family_Name=\"OLAVARRIETA\" Given_Name=\"Ricardo\" Initial=\"R.\" ScbName1=\"Ricardo OLAVARRIETA\" ScbName4=\"R. OLAVARRIETA\" Gender=\"M\" Nation=\"ISU\" Club=\"\" Function=\"STS\"/></Segment_Official_List><Segment_Start_List><Performance ID=\"33\" Start_Number=\"1\" Start_Group_Number=\"1\" PElmScore=\"0.00\" Personal_Best=\"0.00\" Personal_Best_Tot=\"0.00\" Status=\"REM\" Season_Best=\"0.00\" Season_Best_Tot=\"0.00\" Season_Best_Rank=\"0\" Season_Best_Index=\"3\" Season_Best_Tot_Rank=\"0\" Season_Best_Tot_Index=\"3\" StartTime=\"\" Prf_ID=\"3\"><Planned_Element_List/></Performance><Performance ID=\"18\" Start_Number=\"2\" Start_Group_Number=\"1\" PElmScore=\"0.00\" Personal_Best=\"0.00\" Personal_Best_Tot=\"0.00\" Status=\"REM\" Season_Best=\"0.00\" Season_Best_Tot=\"0.00\" Season_Best_Rank=\"0\" Season_Best_Index=\"1\" Season_Best_Tot_Rank=\"0\" Season_Best_Tot_Index=\"1\" StartTime=\"\" Prf_ID=\"2\"><Planned_Element_List/></Performance><Performance ID=\"47\" Start_Number=\"3\" Start_Group_Number=\"1\" PElmScore=\"0.00\" Personal_Best=\"0.00\" Personal_Best_Tot=\"0.00\" Status=\"REM\" Season_Best=\"0.00\" Season_Best_Tot=\"0.00\" Season_Best_Rank=\"0\" Season_Best_Index=\"5\" Season_Best_Tot_Rank=\"0\" Season_Best_Tot_Index=\"5\" StartTime=\"\" Prf_ID=\"4\"><Planned_Element_List/></Performance><Performance ID=\"390\" Start_Number=\"4\" Start_Group_Number=\"1\" PElmScore=\"0.00\" Personal_Best=\"0.00\" Personal_Best_Tot=\"0.00\" Status=\"REM\" Season_Best=\"0.00\" Season_Best_Tot=\"0.00\" Season_Best_Rank=\"0\" Season_Best_Index=\"2\" Season_Best_Tot_Rank=\"0\" Season_Best_Tot_Index=\"2\" StartTime=\"\" Prf_ID=\"5\"><Planned_Element_List/></Performance><Performance ID=\"36\" Start_Number=\"5\" Start_Group_Number=\"1\" PElmScore=\"0.00\" Personal_Best=\"0.00\" Personal_Best_Tot=\"0.00\" Status=\"REM\" Season_Best=\"0.00\" Season_Best_Tot=\"0.00\" Season_Best_Rank=\"0\" Season_Best_Index=\"4\" Season_Best_Tot_Rank=\"0\" Season_Best_Tot_Index=\"4\" StartTime=\"\" Prf_ID=\"1\"><Planned_Element_List/></Performance></Segment_Start_List><Warmup_Group_List><Warmup_Group Index=\"0\" Number=\"5\"/><Warmup_Group Index=\"1\" Number=\"0\"/><Warmup_Group Index=\"2\" Number=\"0\"/><Warmup_Group Index=\"3\" Number=\"0\"/><Warmup_Group Index=\"4\" Number=\"0\"/><Warmup_Group Index=\"5\" Number=\"0\"/><Warmup_Group Index=\"6\" Number=\"0\"/><Warmup_Group Index=\"7\" Number=\"0\"/><Warmup_Group Index=\"8\" Number=\"0\"/><Warmup_Group Index=\"9\" Number=\"0\"/><Warmup_Group Index=\"10\" Number=\"0\"/><Warmup_Group Index=\"11\" Number=\"0\"/><Warmup_Group Index=\"12\" Number=\"0\"/><Warmup_Group Index=\"13\" Number=\"0\"/><Warmup_Group Index=\"14\" Number=\"0\"/><Warmup_Group Index=\"15\" Number=\"0\"/><Warmup_Group Index=\"16\" Number=\"0\"/><Warmup_Group Index=\"17\" Number=\"0\"/><Warmup_Group Index=\"18\" Number=\"0\"/><Warmup_Group Index=\"19\" Number=\"0\"/><Warmup_Group Index=\"20\" Number=\"0\"/><Warmup_Group Index=\"21\" Number=\"0\"/><Warmup_Group Index=\"22\" Number=\"0\"/><Warmup_Group Index=\"23\" Number=\"0\"/><Warmup_Group Index=\"24\" Number=\"0\"/></Warmup_Group_List></Segment><Segment ID=\"2\" Name=\"Free Skating\" Abbreviation=\"FS\" Name_Of_Dance=\"\" Type=\"F\" Number_Of_Judges=\"10\" Number_Of_Decisive_Judges=\"10\" Group=\"\" QCrit=\" \" QNumber=\"0\" ExtDt=\"\" Medal=\"0\"/></Segment_List></Category></Category_List></Event></Segment_Start></Isu_Osis>\x0D\x0D\x0A\x03\x20\x0D\x0A");

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

void UnittestTest::ReceiveSegmentStart()
{
   QByteArray qbaReq(data2);
   OsisLintTestInit();
   osisLink->processData(qbaReq);
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
