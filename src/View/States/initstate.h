#ifndef INITSTATE_H
#define INITSTATE_H
#include "BaseState.h"

class InitState:public BaseState
{
public:
    InitState():BaseState(STATE::INIT){}
    virtual int Process(int event, Params params)
    {
        switch()
    }
};

#endif // INITSTATE_H
