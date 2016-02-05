#ifndef OSISELEMENT_H
#define OSISELEMENT_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include <osisdata.h>

class OsisElement : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisElement(QDomElement& osisElement, QObject *parent = 0);

   inline int GetIndex() { return Ind; }

public:
   enum OsisElementAttributes
   {
      Index, //Index, used as identifier
      Elm_Name, // 80
      Elm_Time, // 4, Time within the program
      Elm_Invalid, // 0 or 1, 1 if base value = 0
      PName, // 80, Name of planned element (without level)
      PBVal, // 20, Base value of planned element, Format “9.9”, Based on level 1
      Points, // Score of the element, Format “9.99”
      Elm_XBV, // Base value of executed element Format “9.99”
      Elm_XGOE, // Grade of execution of element Format “9.99”
      Elm_Info, // 5, Element info (e.g. wrong edge)
      Elm_Half // 1 – for element not in second half 2 – for element in second half
   };
   Q_ENUM(OsisElementAttributes)

private:
   int Ind;
};

typedef QMap <int, OsisElement*> OsisElementMap;

#endif // OSISELEMENT_H
