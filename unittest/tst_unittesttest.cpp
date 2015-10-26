#include <QString>
#include <QtTest>
#include "../dsu_osis/osisdataif.h"

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
};

UnittestTest::UnittestTest()
{
}

void UnittestTest::initTestCase()
{
}

void UnittestTest::cleanupTestCase()
{
}

void UnittestTest::testCase1()
{
   QVERIFY2(true, "Failure");
}

void UnittestTest::testCase2()
{
   QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnittestTest)

#include "tst_unittesttest.moc"
