#include <osis_unittest.h>

void UnittestTest::OsisXmlTestInit()
{
   osisLink = new CalcConnectionThread();
   osisDataIf = new OsisDataProvider();
   osisLink->setDataIf(osisDataIf);
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

void UnittestTest::ParseOsisMsg()
{
   OsisXmlTestInit();

   QByteArray qba;
   QString filename("../unittest/data/event.xml");
   QVERIFY(GetXmlData(qba, filename));
   osisLink->processData(qba);

   OsisXmlTestClean();
}

