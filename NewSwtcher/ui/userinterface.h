#include <QWidget>
#include <QGroupBox>
#include <QStackedWidget>
#include "ipconnectui.h"
#include <configuration.h>

class UserInterface : public QWidget
{
   Q_OBJECT
public:
   explicit UserInterface(Configuration& config, QWidget *parent = nullptr);

signals:

public slots:

private:
   IpConnectUi* qw_calcFsUi;
   IpConnectUi* qw_ObsUi;
};
