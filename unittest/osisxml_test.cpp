#include <osis_unittest.h>

void UnittestTest::OsisXmlTestInit()
{
   osisLink = new CalcConnectionThread();
   competition = new IsuCompetition();
   osisLink->setDataIf(competition->GetDataIf());
}

void UnittestTest::OsisXmlTestClean()
{
   osisLink->setDataIf(0);
   delete osisLink;
   delete osisDataIf;
}

bool UnittestTest::GetXmlData(QByteArray& qba, const QString &filename)
{
   QFile file(filename);
   if (!file.open(QIODevice::ReadOnly))
   {
       return false;
   }
   qba = file.readAll();
   file.close();
   return true;
}

void UnittestTest::ParseOsisEventOverview()
{
   OsisXmlTestInit();

   QByteArray qba;
   QString filename("../unittest/data/event.xml");
   QVERIFY(GetXmlData(qba, filename));
   osisLink->processData(qba);

   OsisXmlTestClean();
}

void UnittestTest::ParseOsisSegmentStart()
{
   OsisXmlTestInit();

   QByteArray qba;
   QString filename("../unittest/data/seg_start.xml");
   QVERIFY(GetXmlData(qba, filename));
   osisLink->processData(qba);

   OsisXmlTestClean();
}

void UnittestTest::ParseOsisAction()
{
   OsisXmlTestInit();

   QByteArray qba;
   QString filename("../unittest/data/actions.xml");
   QVERIFY(GetXmlData(qba, filename));
   osisLink->processData(qba);

   OsisXmlTestClean();
}

void UnittestTest::ParseOsisAll()
{
//   OsisXmlTestInit();

//   QByteArray qba;
//   QString filename("../unittest/data/log_xml.xml");
//   QVERIFY(GetXmlData(qba, filename));
//   osisLink->processData(qba);

//   OsisXmlTestClean();
}
