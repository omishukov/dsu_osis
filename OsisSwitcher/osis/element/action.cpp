/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "action.h"

OsisAction::OsisAction(QDomElement& osisElement, QString& elementName, QObject *parent)
   : QObject(parent)
   , OsisData(OsisAction::staticMetaObject, osisElement, elementName)
   , Current_Participant_Id(GetAttributeInt(Current_Participant_ID))
{
}
