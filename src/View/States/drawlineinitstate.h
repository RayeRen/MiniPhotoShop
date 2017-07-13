#ifndef DRAWLINEINITSTATE_H
#define DRAWLINEINITSTATE_H
#include "BaseState.h"
#include "../statemanager.h"

#include "../mainwindow.h"

class DrawLineInitState:public BaseState
{
public:
    DrawLineInitState():BaseState(STATE::DRAW_LINE_INIT){}
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
            pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定直线的终点")));
           pMainWindow->ui->MainDisplayWidget->update();
        }
            return STATE::DRAW_LINE;
            break;
         default:return GetNumber();
        }

    }
};

#endif // DRAWLINEINITSTATE_H
