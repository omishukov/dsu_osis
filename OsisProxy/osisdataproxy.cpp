#include <QByteArray>
#include <QDomDocument>
#include <QDebug>
#include <QMetaEnum>
#include <QMutexLocker>
#include "osisdataproxy.h"
#include "element/action.h"

const static QByteArray STX("\x02");
const static QByteArray ETX("\x03");

OsisDataProxy::OsisDataProxy(QObject *parent)
   : QObject(parent)
   , DataIf(0)
   , Tag(-1)
{

}

void OsisDataProxy::SendCache(QTcpSocket *socket)
{
   QMutexLocker lock(&M);

   if (!EventOverview.isEmpty())
   {
      socket->write(EventOverview);
      socket->flush();
   }
   if (!SegmentStart.isEmpty())
   {
      socket->write(SegmentStart);
      socket->flush();
   }
   if (!PrfRanking.isEmpty())
   {
      socket->write(PrfRanking);
      socket->flush();
   }
   if (!ActionIni.isEmpty())
   {
      socket->write(ActionIni);
      socket->flush();
   }
}

void OsisDataProxy::ProcessData()
{
   QMutexLocker lock(&M);

   if (DataIf)
   {
      QByteArray* data = 0;
      data = DataIf->GetData();
      if (data)
      {
         qDebug() << "New data";
         Handle (data);
      }
   }
}

void OsisDataProxy::Handle(QByteArray* qba)
{
   Cache(qba);
   qba->prepend(STX);
   qba->append(ETX);
   emit Distribute(qba);
}

void OsisDataProxy::Cache(QByteArray* qba)
{
   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;

   if (!doc.setContent(*qba, &errMsg, &errLine, &errColumn))
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

   Tag = -1;
   if (ProcessOsisTree(n) && Tag != -1)
   {
      switch(Tag)
      {
         case Event_Overview:
         {
            EventOverview.clear();
            EventOverview.append(STX);
            EventOverview.append(*qba);
            EventOverview.append(ETX);
            SegmentStart.clear();
            PrfRanking.clear();
            ActionIni.clear();
         }
            break;
         case Segment_Start:
         {
            SegmentStart.clear();
            if (!EventOverview.isEmpty())
            {
               SegmentStart.append(STX);
               SegmentStart.append(*qba);
               SegmentStart.append(ETX);
            }
         }
            break;
         case Prf_Ranking:
         {
            PrfRanking.clear();
            if (!EventOverview.isEmpty() && !SegmentStart.isEmpty())
            {
               PrfRanking.append(STX);
               PrfRanking.append(*qba);
               PrfRanking.append(ETX);
            }
         }
            break;
         case Action:
         {
            ActionIni.clear();
            if (!EventOverview.isEmpty() && !SegmentStart.isEmpty() && !PrfRanking.isEmpty())
            {
               ActionIni.append(STX);
               ActionIni.append(*qba);
               ActionIni.append(ETX);
            }
         }
            break;
         default:
            break;
      }

   }

}

bool OsisDataProxy::ProcessOsisTree(QDomNode& n)
{
   if (!ProcessOsisElement(n))
   {
      return false;
   }
   QDomNode node = n.firstChild();

   while(!node.isNull() && ProcessOsisTree(node))
   {
      node = node.nextSibling();
   }
   return true;
}

bool OsisDataProxy::ProcessOsisElement(QDomNode& n)
{
   if (n.isNull() || (n.nodeType() != QDomNode::ElementNode))
   {
      return true;
   }

   QDomElement e = n.toElement();
   if(e.isNull())
   {
      // Warning: An empty element
      return true;
   }

   const QMetaObject &mo = OsisDataProxy::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisXmlElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   QString elementName = e.tagName();
   int xmlElementTag = metaEnum.keyToValue(elementName.toLocal8Bit().constData());
   switch(xmlElementTag)
   {
      case Event_Overview:
      {
         Tag = xmlElementTag;
      }
         break;
      case Segment_Start:
      {
         Tag = xmlElementTag;
      }
         break;
      case Prf_Ranking:
      {
         Tag = xmlElementTag;
      }
         break;
      case Action:
      {
         OsisAction* action = new OsisAction(e, elementName);
         QString elementName = action->GetAttribute(OsisAction::Command);
         if (!QString::compare(elementName, "INI"))
         {
            QString id = action->GetAttribute(OsisAction::Current_Participant_ID);
            id.prepend("Current_Participant_ID=\"");
            id.append("\"");
            CurrentPaticipantId = id;

            QString nid = action->GetAttribute(OsisAction::Next_Participant_ID);
            nid.prepend("Next_Participant_ID=\"");
            nid.append("\"");
            NextPaticipantId = nid;

            QString pid = action->GetAttribute(OsisAction::Prev_Participant_ID);
            pid.prepend("Prev_Participant_ID=\"");
            pid.append("\"");
            PrevPaticipantId = pid;

            QString npid = action->GetAttribute(OsisAction::Next_Participant_StNum);
            npid.prepend("Next_Participant_StNum=\"");
            npid.append("\"");
            NextParticipantStNum = npid;

            QString lpid = action->GetAttribute(OsisAction::LastScored_Participant_StNum);
            lpid.prepend("LastScored_Participant_StNum=\"");
            lpid.append("\"");
            LastScoredParticipantStNum = lpid;

            Tag = xmlElementTag;
         }
         else if (!QString::compare(elementName, "STP"))
         {
            ActionIni.clear();
         }
         else if (!QString::compare(elementName, "NXT"))
         {
            QString id = action->GetAttribute(OsisAction::Current_Participant_ID);
            id.prepend("Current_Participant_ID=\"");
            id.append("\"");
            ActionIni.replace(CurrentPaticipantId, id.toLocal8Bit().constData());
            CurrentPaticipantId = id;

            QString nid = action->GetAttribute(OsisAction::Next_Participant_ID);
            nid.prepend("Next_Participant_ID=\"");
            nid.append("\"");
            ActionIni.replace(NextPaticipantId, nid.toLocal8Bit().constData());
            NextPaticipantId = nid;

            QString pid = action->GetAttribute(OsisAction::Prev_Participant_ID);
            pid.prepend("Prev_Participant_ID=\"");
            pid.append("\"");
            ActionIni.replace(PrevPaticipantId, pid.toLocal8Bit().constData());
            PrevPaticipantId = pid;

            QString npid = action->GetAttribute(OsisAction::Next_Participant_StNum);
            npid.prepend("Next_Participant_StNum=\"");
            npid.append("\"");
            ActionIni.replace(NextParticipantStNum, npid.toLocal8Bit().constData());
            NextParticipantStNum = npid;

            QString lpid = action->GetAttribute(OsisAction::LastScored_Participant_StNum);
            lpid.prepend("LastScored_Participant_StNum=\"");
            lpid.append("\"");
            ActionIni.replace(LastScoredParticipantStNum, lpid.toLocal8Bit().constData());
            LastScoredParticipantStNum = lpid;
         }
      }
         break;
      default:
         break;
   }

   return true;
}
