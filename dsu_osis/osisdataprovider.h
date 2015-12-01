#ifndef OSISDATAPROVIDER_H
#define OSISDATAPROVIDER_H

#include <QObject>
#include <QByteArray>
#include "osisdataif.h"

// Action codes (AC) started with a number cannot be used in enums.
// Add a prefix to received AC string before using it in QMetaEnum.
const QString ActionCodePrefix = "AC_";

class OsisDataProvider: public QObject, public OsisDataIf
{
   Q_OBJECT
public:
   OsisDataProvider();
   ~OsisDataProvider() {}

public:
   virtual void DataInd(class QByteArray& qba);

public:
   enum OsisMessageType
   {
      Event_Overview,
      Segment_Start,
      Segment_Running,
      Segment_Statistic
   };

   enum OsisSegmentRunningAction
   {
      AC_1SC,
      AC_1S1,
      AC_1S2,
      AC_1S3,
      AC_1S4,
      AC_1S5,
      AC_2SC,
      AC_3SC,
      AC_CLR,
      AC_ELM,
      AC_ELS,
      AC_INI,
      AC_IDT,
      AC_IRS,
      AC_JDG,
      AC_LTV,
      AC_NAM,
      AC_NXP,
      AC_RES,
      AC_SEG,
      AC_STL,
      AC_STP, // Stop
      AC_NXT, // Next performer
      AC_PRV, // Previous performer
      AC_TBW, // Time count backward
      AC_TFW, // Time count forward
      AC_TR1, // Overall team standing
      AC_TR2, // Overall team standing
      AC_TST, // Time stopped
      AC_TPA, // Time pause
      AC_TCL, // Clear time
      AC_TIM, // Time value
      AC_URK, // Ranking Update
      AC_VTR, // Victory Ceremony
      AC_WUP  // send warm up group
   };

   Q_ENUMS(OsisMessageType)
   Q_ENUMS(OsisSegmentRunningAction)
};

#endif // OSISDATAPROVIDER_H
