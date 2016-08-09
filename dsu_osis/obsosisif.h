#ifndef OBSOSISIF_H
#define OBSOSISIF_H

#include <QString>

class ObsOsisIf
{
public:
   virtual ~ObsOsisIf() {}

   virtual QString GetCurrentParticipantName(class IsuOsis *newIsuOsis) = 0;
};

#endif // OBSOSISIF_H
