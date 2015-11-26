#ifndef OSIS_UNITTEST_H
#define OSIS_UNITTEST_H
#include <QtTest>
#include "../dsu_osis/osisdataif.h"
#include "../dsu_osis/calcconnectionthread.h"

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

#endif // OSIS_UNITTEST_H
