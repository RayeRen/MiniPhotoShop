#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "States/BaseState.h"
#include <map>

class MainWindow;

using namespace std;
class StateManager{
    static MainWindow *pMainWindow;

    static int currentState;
    static map<int,shared_ptr<BaseState>> stateMap;
public:
    static void Init();
    static void Run(int event,Params params=Params());
    static void AddState(shared_ptr<BaseState> newState){stateMap.insert(pair<int,shared_ptr<BaseState>>(newState->GetNumber(),newState));}
    static int GetState(){return currentState;}
    static void SetpMainWindow(MainWindow* pMainWindow){StateManager::pMainWindow=pMainWindow;}
    static MainWindow* GetpMainWindow(){return pMainWindow;}
};

#endif // STATEMANAGER_H
