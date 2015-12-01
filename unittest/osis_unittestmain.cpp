#include <QString>
#include <osis_unittest.h>

UnittestTest::UnittestTest()
{
   osisLink = 0;
   osisDataStubIf = 0;
   osisDataIf = 0;
}

void UnittestTest::initTestCase()
{
}

void UnittestTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(UnittestTest)
