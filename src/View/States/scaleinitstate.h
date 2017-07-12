#ifndef SCALEINITSTATE_H
#define SCALEINITSTATE_H
#include "BaseState.h"
class ScaleInitState:public BaseState
{
public:
   ScaleInitState():BaseState(STATE::SCALE_INIT){}
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
           pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下以缩放图层")));
          {
               Params params;
               params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->setParams(params);
               pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->exec();
           }

           pMainWindow->ui->MainDisplayWidget->update();
       }
           return STATE::SCALE;
           break;
       default:return GetNumber();
       }
    }
};
#endif // SCALEINITSTATE_H
