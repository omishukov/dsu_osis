#include <QHBoxLayout>
#include <QVBoxLayout>
#include "userinterface.h"

UserInterface::UserInterface(LinkIf& osisLinkIf, LinkIf& obsLinkIf, QWidget *parent)
   : QWidget(parent)
{
   qw_calcFsUi = new IpConnectUi(osisLinkIf);
   qw_ObsUi = new IpConnectUi(obsLinkIf);

   QHBoxLayout *connectionLayout = new QHBoxLayout;
   connectionLayout->addWidget(qw_calcFsUi);
   connectionLayout->addWidget(qw_ObsUi);

   QHBoxLayout *currentStatusInfoLayout = new QHBoxLayout;
   currentStatusInfoLayout->addWidget(qw_calcFsUi);
   currentStatusInfoLayout->addWidget(qw_ObsUi);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addLayout(connectionLayout);
   mainLayout->addStretch(1);
   setLayout(mainLayout);
}
