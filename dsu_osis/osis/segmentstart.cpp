/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "segmentstart.h"

OsisSegmentStart::OsisSegmentStart(QDomElement& segmentStartElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisSegmentStart::staticMetaObject, "SegmentStart")
{
   ProcessAttributes(segmentStartElement);
}
