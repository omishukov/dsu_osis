#include <QString>
#include <osis_unittest.h>

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

QTEST_APPLESS_MAIN(UnittestTest)
