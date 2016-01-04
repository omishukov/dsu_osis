#ifndef OSISDEDUCTION_H
#define OSISDEDUCTION_H

#include <QObject>
#include <QDomDocument>
#include <QMap>

class OsisDeduction : public QObject
{
   Q_OBJECT
public:
   explicit OsisDeduction(QObject *parent = 0);

signals:

public slots:

public:
   enum OsisDeductionAttributes
   {
      Index, // Index, used as identifier
      Ded_Name, // 40
      Ded_Value, // Format “9.99”
      Ded_Edit
   };
   Q_ENUM(OsisDeductionAttributes)

   int GetIndex() { return DedIndex; }
   QString GetName() { return DedName; }
   double GetValue() { return DedValue; }
   QString GetEdit() { return DedEdit; }
   bool ProcessDeductionAttributes(QDomElement& deductionElement);

private:
   int DedIndex;
   QString DedName;
   double DedValue;
   QString DedEdit;

   OsisDeduction& operator=(const OsisDeduction &copy);

};

typedef QMap <int, OsisDeduction*> OsisDeductionMap;

#endif // OSISDEDUCTION_H
