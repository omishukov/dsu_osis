#ifndef UILINKIF_H
#define UILINKIF_H

class UiLinkIf
{
public:
   virtual void LinkConnected() = 0;
   virtual void LinkDisconnected() = 0;
};

#endif // UILINKIF_H
