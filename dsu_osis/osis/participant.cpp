/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "participant.h"

OsisParticipant::OsisParticipant(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisParticipant::staticMetaObject, "Participant")
{
   ProcessAttributes(osisElement);

   bool ok;
   Id = GetAttribute(OsisParticipant::ID).toInt(&ok);
   if (!ok)
   {
      Id = -1;
      qCritical() << "Wrong Participant ID: " << GetAttribute(OsisParticipant::ID) << ", Name:" << GetAttribute(OsisParticipant::Full_Name) << endl;
   }
}

OsisParticipant::~OsisParticipant()
{
   foreach(OsisAthlete* athlete, Athletes)
   {
      delete athlete;
   }
}

void OsisParticipant::AddAthlete(OsisAthlete* newAthlete)
{
   if (newAthlete->GetId() != -1)
   {
      Athletes.insert(newAthlete->GetId(), newAthlete);
   }
}
