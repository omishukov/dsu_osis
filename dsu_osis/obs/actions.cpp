#include <QMetaEnum>
#include "actions.h"

Actions::Actions()
{
}

void Actions::DoActions()
{
   foreach(int action, ActionList)
   {
      switch (action)
      {
         case ACTION_1SC:
            break;
         case ACTION_1S1:
            break;
         case ACTION_1S2:
            break;
         case ACTION_1S3:
            break;
         case ACTION_1S4:
            break;
         case ACTION_1S5:
            break;
         case ACTION_2SC:
            break;
         case ACTION_3SC:
            break;
         case ACTION_CLR:
            break;
         case ACTION_ELM:
            break;
         case ACTION_ELS:
            break;
         case ACTION_INI:
            break;
         case ACTION_IDT:
            break;
         case ACTION_IRS:
            break;
         case ACTION_JDG:
            break;
         case ACTION_LTV:
            break;
         case ACTION_NAM:
            break;
         case ACTION_NXP:
            break;
         case ACTION_RES:
            break;
         case ACTION_SEG:
            break;
         case ACTION_STL:
            break;
         case ACTION_STP:
            break;
         case ACTION_NXT:
            break;
         case ACTION_PRV:
            break;
         case ACTION_TBW:
            break;
         case ACTION_TFW:
            break;
         case ACTION_TR1:
            break;
         case ACTION_TR2:
            break;
         case ACTION_TST:
            break;
         case ACTION_TPA:
            break;
         case ACTION_TCL:
            break;
         case ACTION_TIM:
            break;
         case ACTION_URK:
            break;
         case ACTION_VTR:
            break;
         case ACTION_WUP:
            break;
         case EVENT_OVERVIEW:
            break;
         case SEGMENT_START:
            break;
         case PRF_RANKING:
            break;
         default:
            break;
      }
   }
   ActionList.clear();
}

void Actions::AddAction(int action)
{
   ActionList.push_back(action);
}
