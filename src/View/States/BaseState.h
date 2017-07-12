#ifndef BASESTATE_H
#define BASESTATE_H
#include "../../Constants.h"
#include "../../Common/Params.h"

class BaseState{
int number;
public:
    BaseState(int number):number(number){}
    virtual int Process(int event,Params params)=0;
    int GetNumber(){return number;}
};

#endif
