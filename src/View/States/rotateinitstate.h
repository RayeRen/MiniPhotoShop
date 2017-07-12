#ifndef ROTATEINITSTATE_H
#define ROTATEINITSTATE_H
#include "BaseState.h"
class RotateInitState:public BaseState
{
public:
   RotateInitState():BaseState(STATE::ROTATE_INIT){}
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
           pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下以旋转图层")));
          {
               Params params;
               params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->setParams(params);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->exec();
           }
           pMainWindow->ui->MainDisplayWidget->update();

       }
           return STATE::ROTATE;
           break;
default:return GetNumber();
       }
    }
};
#endif // ROTATEINITSTATE_H
