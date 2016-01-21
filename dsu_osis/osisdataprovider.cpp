/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QtDebug>
#include "osisdataprovider.h"
#include "osis/event.h"

OsisDataProvider::OsisDataProvider()
   : osisMsg(new OsisXml())
{

}

OsisDataProvider::~OsisDataProvider()
{
   delete osisMsg;
}

void OsisDataProvider::DataInd(QByteArray& qba)
{
   QByteArray osisData;
   osisData.swap(qba);

   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;
   if (!doc.setContent(osisData, &errMsg, &errLine, &errColumn))
   {
      qCritical() << "XML Parser Error " << errMsg << " (" << errLine << ":" << errColumn << ")" << endl;
      return;
   }
   QDomElement docElem = doc.documentElement();

   if (!docElem.tagName().contains("Isu_Osis"))
   {
      qCritical() << "XML Parser Error: the message shall start with <Isu_Osis>" << endl;
      return;
   }

   QDomNode n = docElem.firstChild();
   osisMsg->ProcessOsisData(n);
}

