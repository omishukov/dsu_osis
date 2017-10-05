#include <QHBoxLayout>
#include <QVBoxLayout>
#include "userinterface.h"

const QString IsuCalcFsGroupName = "IsuCalcFs";
const QString ObsGroupName = "OBS";

UserInterface::UserInterface(Configuration &config, QWidget *parent)
   : QWidget(parent)
{
   qw_calcFsUi = new IpConnectUi(config, IsuCalcFsGroupName);
   qw_ObsUi = new IpConnectUi(config, ObsGroupName);

   QHBoxLayout *connectionLayout = new QHBoxLayout;
   connectionLayout->addWidget(qw_calcFsUi);
   connectionLayout->addWidget(qw_ObsUi);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addLayout(connectionLayout);
   mainLayout->addStretch(1);
   setLayout(mainLayout);
}
