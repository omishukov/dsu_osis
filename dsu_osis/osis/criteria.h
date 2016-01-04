#ifndef OSISCRITERIA_H
#define OSISCRITERIA_H

#include <QObject>
#include <QDomDocument>
#include <QMap>

class OsisCriteria : public QObject
{
   Q_OBJECT
public:
   explicit OsisCriteria(int segmentId, QObject *parent = 0);
   OsisCriteria& operator=(const OsisCriteria &copy);

   int GetSegmentId() { return SegmentId; }
   int GetIndex() { return CriIndex; }
   QString GetName() { return CriName; }
   QString GetAbbrev() { return CriAbbrev; }
   double GetFactor() { return CriFactor; }
   double GetPoints() { return CriPoints; }

   bool ProcessCriteriaAttributes(QDomElement& criteriaElement);

public:
   enum OsisCriteriaAttributes
   {
      Index, //  Index, used as identifier
      Cri_Name, // 40
      Cri_Abbrev, // 10
      Cri_Factor, //  Format “9.99”
      Points //  Format “9.99”
   };
   Q_ENUM(OsisCriteriaAttributes)

signals:

public slots:

private:
   int SegmentId;
   int CriIndex;
   QString CriName;
   QString CriAbbrev;
   double CriFactor;
   double CriPoints;

};

typedef QMap <int, OsisCriteria*> OsisCriteriaMap;

#endif // OSISCRITERIA_H
