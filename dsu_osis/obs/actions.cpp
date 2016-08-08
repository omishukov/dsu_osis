#include <QMetaEnum>
#include "actions.h"

Actions::Actions()
{
}

void Actions::AddAction(int action)
{
   ActionList.push_back(action);
}
