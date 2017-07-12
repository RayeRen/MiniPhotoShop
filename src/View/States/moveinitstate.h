#ifndef MOVEINITSTATE_H
#define MOVEINITSTATE_H
#include "BaseState.h"
class MoveInitState:public BaseState
{
public:
   MoveInitState():BaseState(STATE::MOVE_INIT){}
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
           pMainWindow->ui->MainDisplayWidget->mouseX=ints[0];
           pMainWindow->ui->MainDisplayWidget->mouseY=ints[1];
           pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下以移动图层")));
          {
               Params params;
               params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->setParams(params);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->exec();
           }

           pMainWindow->ui->MainDisplayWidget->update();
       }
           return STATE::MOVE;
           break;
           default:return GetNumber();
       }
    }
};
#endif // MOVEINITSTATE_H
