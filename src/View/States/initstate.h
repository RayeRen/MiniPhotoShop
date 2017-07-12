#ifndef INITSTATE_H
#define INITSTATE_H
#include "BaseState.h"
#include "statecommonaction.h"
class InitState:public BaseState
{
public:
    InitState():BaseState(STATE::INIT){}
    virtual int Process(int event, Params params)
    {
        switch(event)
        {
        case EVENT::ACTION_TRIGGERED:
            return StateCommonAction::ActionTrigged(GetNumber(),params);
            break;
        default:return GetNumber();
        }

    }
};

#endif // INITSTATE_H
