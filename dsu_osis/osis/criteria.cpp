#include <QMetaEnum>
#include "criteria.h"

OsisCriteria::OsisCriteria(int segmentId, QObject *parent)
   : QObject(parent)
   , SegmentId(segmentId)
   , CriIndex(-1)
   , CriFactor(-1)
   , CriPoints(-1)
{
}

OsisCriteria& OsisCriteria::operator=(const OsisCriteria& copy)
{
   if (this == &copy)
   {
      return *this;
   }

   if (copy.CriIndex != -1)
   {
      CriIndex = copy.CriIndex;
   }
   if (!copy.CriName.isNull())
   {
      CriName = copy.CriName;
   }
   if (!copy.CriAbbrev.isNull())
   {
      CriAbbrev = copy.CriAbbrev;
   }
   if (copy.CriFactor != -1)
   {
      CriFactor = copy.CriIndex;
   }
   if (copy.CriPoints != -1)
   {
      CriPoints = copy.CriPoints;
   }

   return *this;
}

bool OsisCriteria::ProcessCriteriaAttributes(QDomElement& criteriaElement)
{
   const QMetaObject &mo = OsisCriteria::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisCriteriaAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);

   // Parse and save <Criteria> attributes
   QDomNamedNodeMap attr = criteriaElement.attributes();
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
         case Index:
            CriIndex = at.value().toInt();
            break;
         case Cri_Name:
            CriName = at.value();
            break;
         case Cri_Abbrev:
            CriAbbrev = at.value();
            break;
         case Cri_Factor:
            CriFactor = at.value().toDouble();
            break;
         case Points:
            CriPoints = at.value().toDouble();
            break;
         default:
            break;
      }
   }

   return true;
}

