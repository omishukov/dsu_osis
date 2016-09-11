/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "prfranking.h"

OsisPrfRanking::OsisPrfRanking(QDomElement& categoryElement, QString& elementName, QObject *parent)
   : QObject(parent)
   , OsisData(OsisPrfRanking::staticMetaObject, categoryElement, elementName)
{
}
