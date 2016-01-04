#include <osis_unittest.h>
#include <QByteArray>
#include <QDomDocument>

bool PrintElement(QDomNode& n)
{
   if (n.isNull() || (n.nodeType() != QDomNode::ElementNode))
   {
      return false;
   }
   QDomElement e = n.toElement();
   qDebug() << e.tagName() << endl;
   return true;
}

bool WalkOsisXml(QDomNode& n)
{
   if (!PrintElement(n))
   {
      return false;
   }
   QDomNode node = n.firstChild();

   while(!node.isNull() && WalkOsisXml(node))
   {
      node = node.nextSibling();
   }
   return true;
}

void UnittestTest::RecursiveTest()
{
   OsisXmlTestInit();

   QByteArray qba;
   QString filename("../unittest/data/event_clear.xml");
   QVERIFY(GetXmlData(qba, filename));

   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;
   if (!doc.setContent(qba, &errMsg, &errLine, &errColumn))
   {
      qDebug() << "XML Parser Error " << errMsg << " (" << errLine << ":" << errColumn << ")" << endl;
      return;
   }
   QDomElement docElem = doc.documentElement();

   QDomNode n = docElem.firstChild();

   WalkOsisXml(n);

   OsisXmlTestClean();

}
