#ifndef ADDRECTINITSTATE_H
#define ADDRECTINITSTATE_H
#include "BaseState.h"
class DrawRectInitState:public BaseState
{
public:
   DrawRectInitState():BaseState(STATE::DRAW_RECT_INIT){}
    virtual int Process(int event, Params params)
    {
       switch(event)
       {
       case EVENT::ACTION_TRIGGERED:
           return StateCommonAction::ActionTrigged(GetNumber(),params);
           break;
       case EVENT::MOUSE_LEFT_PRESSED:
       {
           vector<int> ints=params.getInts();
           MainWindow* pMainWindow=StateManager::GetpMainWindow();
           pMainWindow->ui->MainDisplayWidget->mouseX=pMainWindow->ui->MainDisplayWidget->mouseLastX=ints[0];
           pMainWindow->ui->MainDisplayWidget->mouseY=pMainWindow->ui->MainDisplayWidget->mouseLastY=ints[1];
           pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定矩形的第二个顶点 ")));
          pMainWindow->ui->MainDisplayWidget->update();
       }
           return STATE::DRAW_RECT;
           break;
           default:return GetNumber();
       }
    }
};
#endif // ADDRECTINITSTATE_H
