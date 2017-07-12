#ifndef DRAWELLIPSEINITSTATE_H
#define DRAWELLIPSEINITSTATE_H
#include "BaseState.h"
class DrawEllipseInitState:public BaseState
{
public:
   DrawEllipseInitState():BaseState(STATE::DRAW_ELLIPSE_INIT){}
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
           pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定椭圆的长轴与短轴")));
          pMainWindow->ui->MainDisplayWidget->update();
       }
           return STATE::DRAW_ELLIPSE;
           break;
           default:return GetNumber();
       }
    }
};
#endif // DRAWELLIPSEINITSTATE_H
