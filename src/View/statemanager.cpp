#include "statemanager.h"
#include "States/initstate.h"
#include "States/drawlineinitstate.h"
#include "States/drawlinestate.h"
#include "States/drawellipseinitstate.h"
#include "States/drawellipsestate.h"
#include "States/drawrectinitstate.h"
#include "States/drawrectstate.h"
#include "States/moveinitstate.h"
#include "States/movestate.h"
#include "States/rotateinitstate.h"
#include "States/rotatestate.h"
#include "States/scaleinitstate.h"
#include "States/scalestate.h"

int StateManager::currentState=STATE::INIT;
map<int,shared_ptr<BaseState>> StateManager::stateMap;
MainWindow *StateManager::pMainWindow=NULL;

void StateManager::Run(int event,Params params)
{
    currentState=stateMap[currentState]->Process(event,params);
}

void StateManager::Init()
{
    currentState=STATE::INIT;
    AddState(shared_ptr<BaseState>(new InitState()));
    AddState(shared_ptr<BaseState>(new DrawLineState()));
    AddState(shared_ptr<BaseState>(new DrawLineInitState()));
    AddState(shared_ptr<BaseState>(new DrawEllipseInitState()));
    AddState(shared_ptr<BaseState>(new DrawEllipseState()));
    AddState(shared_ptr<BaseState>(new DrawRectInitState()));
    AddState(shared_ptr<BaseState>(new DrawRectState()));
    AddState(shared_ptr<BaseState>(new MoveInitState()));
    AddState(shared_ptr<BaseState>(new MoveState()));
    AddState(shared_ptr<BaseState>(new RotateInitState()));
    AddState(shared_ptr<BaseState>(new RotateState()));
    AddState(shared_ptr<BaseState>(new ScaleInitState()));
    AddState(shared_ptr<BaseState>(new ScaleState()));
}
