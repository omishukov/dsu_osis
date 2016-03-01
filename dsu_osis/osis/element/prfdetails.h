#ifndef OSISPRFDETAILS_H
#define OSISPRFDETAILS_H

#include <QObject>
#include <QDomDocument>
#include <osisdata.h>

class OsisPrfDetails : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisPrfDetails(QDomElement& osisElement, QObject *parent = 0);


public:
   enum OsisElementAttributes
   {
      Points, // Score of the performance, total segment score
      TES, // Technical element score. Format “9.99”
      TCS, // Total component score. Format “9.99”
      Bonus, //
      Ded_Sum, // Sum of all deductions
      Rec // 2. “PB” – personal best
   };
   Q_ENUM(OsisElementAttributes)
};

#endif // OSISPRFDETAILS_H
