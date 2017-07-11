#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "States/BaseState.h"
#include <map>
using namespace std;
class StateManager{

    int currentState;
    map<int,shared_ptr<BaseState>> stateMap;
public:
    StateManager():currentState(0){}
    void Run(int event);
    void AddState(shared_ptr<BaseState> newState)
    {
        map.push_back(pair<int,shared_ptr<BaseState>>(newState->GetNumber(),newState));
    }
    int GetState(){return currentState;}
};

#endif // STATEMANAGER_H
