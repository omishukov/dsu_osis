/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "participant.h"

OsisParticipant::OsisParticipant(QObject *parent)
   : QObject(parent)
   , Participant_ID(-1)
   , Participant_Status(Status_MAX)
{
   for (int i = 0; i < 6; ++i)
   {
      Participant_SegmentStatus[i] = PerfStatus_MAX;
      Participant_SegmentRank[i] = -1;
      Participant_SegmentIndex[i] = -1;
      Participant_SegmentPoints[i] = -1;
      Participant_SegmentIIndex[i] = -1;
      Participant_SegmentIRank[i] = -1;
   }

}

bool OsisParticipant::ProcessAttributes(QDomElement& participantElement)
{
   const QMetaObject &mo = OsisParticipant::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisParticipantAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);

   // Parse and save <Participant> attributes
   QDomNamedNodeMap attr = participantElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case ID:
            Participant_ID = at.value().toInt();
            break;
         case Status:
            {
               uint Status = getEnumKey(OsisParticipant::staticMetaObject, "OsisParticipantStatus", at.value().toLocal8Bit().constData());
               if (Status > Status_MAX)
               {
                  // Error report
                  break;
               }
               Participant_Status = static_cast<enum OsisParticipantStatus>(Status);
            }
            break;
         case Type:
            break;
         case Full_Name:
            break;
         case Short_Name:
            break;
         case TV_Long_Name:
            break;
         case TV_Short_Name:
            break;
         case ScbName1:
            break;
         case ScbName2:
            break;
         case ScbName3:
            break;
         case ScbName4:
            break;
         case Nation:
            break;
         case Music:
            break;
         case Coach:
            break;
         case Club:
            break;
         case ExtRef:
            break;
         case RegNum:
            break;
         case TeamName:
            break;
         case TeamNation:
            break;
         case Index:
            break;
         case TIndex:
            break;
         case TRank:
            break;
         case TPoint:
            break;
         case Segment1_Status:
            break;
         case Segment2_Status:
            break;
         case Segment3_Status:
            break;
         case Segment4_Status:
            break;
         case Segment5_Status:
            break;
         case Segment6_Status:
            break;
         case Segment1_Rank:
            break;
         case Segment2_Rank:
            break;
         case Segment3_Rank:
            break;
         case Segment4_Rank:
            break;
         case Segment5_Rank:
            break;
         case Segment6_Rank:
            break;
         case Segment1_Index:
            break;
         case Segment2_Index:
            break;
         case Segment3_Index:
            break;
         case Segment4_Index:
            break;
         case Segment5_Index:
            break;
         case Segment6_Index:
            break;
         case Segment1_Points:
            break;
         case Segment2_Points:
            break;
         case Segment3_Points:
            break;
         case Segment4_Points:
            break;
         case Segment5_Points:
            break;
         case Segment6_Points:
            break;
         case Segment1_IIndex:
            break;
         case Segment2_IIndex:
            break;
         case Segment3_IIndex:
            break;
         case Segment4_IIndex:
            break;
         case Segment5_IIndex:
            break;
         case Segment6_IIndex:
            break;
         case Segment1_IRank:
            break;
         case Segment2_IRank:
            break;
         case Segment3_IRank:
            break;
         case Segment4_IRank:
            break;
         case Segment5_IRank:
            break;
         case Segment6_IRank:
         default:
            break;
      }
   }

   return true;
}
