#ifndef STATECOMMONACTION_H
#define STATECOMMONACTION_H
#include "BaseState.h"

class StateCommonAction
{
public:
    static int ActionTrigged(int state,Params params);
    static void PerformLayoutMerge();
    static void PerformLaplac();
    static void PerformBilaFilter();
};

#endif // STATECOMMONACTION_H
