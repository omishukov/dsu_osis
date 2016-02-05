#ifndef OSISPRFRANKING_H
#define OSISPRFRANKING_H

#include <QObject>
#include <QDomDocument>
#include <osisdata.h>

class OsisPrfRanking : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisPrfRanking(QDomElement& osisElement, QObject *parent = 0);

public:
   enum OsisElementAttributes
   {
      Gender, // M|F|X
      Type, // See category types
      Rank, // See ranking type
      TypeName
   };
   Q_ENUM(OsisElementAttributes)
};

#endif // OSISPRFRANKING_H
