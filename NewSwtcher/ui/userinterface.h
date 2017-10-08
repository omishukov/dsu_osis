#include <QWidget>
#include <QGroupBox>
#include <QStackedWidget>
#include "ipconnectui.h"
#include <link/linkif.h>

class UserInterface : public QWidget
{
   Q_OBJECT
public:
   explicit UserInterface(LinkIf& osisLinkIf, LinkIf& obsLinkIf, QWidget *parent = nullptr);

signals:

public slots:

private:
   IpConnectUi* qw_calcFsUi;
   IpConnectUi* qw_ObsUi;
};
