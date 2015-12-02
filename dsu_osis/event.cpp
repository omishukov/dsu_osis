#include "event.h"

OsisEvent::OsisEvent()
{
}

OsisEvent::~OsisEvent()
{
}

void OsisEvent::AddEvent(const QDomElement &element)
{
   QDomNode child = element.firstChild();
}
