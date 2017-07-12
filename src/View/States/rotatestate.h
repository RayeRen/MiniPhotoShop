#ifndef ROTATESTATE_H
#define ROTATESTATE_H
#include "BaseState.h"
class RotateState:public BaseState
{
public:
    RotateState():BaseState(STATE::ROTATE){}
    virtual int Process(int event, Params params)
    {
        switch(event)
        {
        case EVENT::ACTION_TRIGGERED:
            return StateCommonAction::ActionTrigged(GetNumber(),params);
            break;
        case EVENT::MOUSE_LEFT_RELEASED:
        {
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            Params params;
            params.setType(COMMAND::LAYOUT_CHANGEEND);
            pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->setParams(params);
            pMainWindow->ui->MainDisplayWidget->layoutTransNotifyCommand->exec();
            pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以开始旋转图层 ")));
            pMainWindow->ui->MainDisplayWidget->update();
        }
            return STATE::ROTATE_INIT;
            break;
        case EVENT::MOUSE_MOVE:
        {
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            vector<int> ints=params.getInts();

            {
                Params params;
                params.setType(COMMAND::LAYOUT_ROTATE);
                params.setDoubles({(double)(ints[0]-pMainWindow->ui->MainDisplayWidget->mouseX)*SETTINGS::ROTATE_STEP});

                pMainWindow->ui->MainDisplayWidget->layoutTransCommand->setParams(params);
                pMainWindow->ui->MainDisplayWidget->layoutTransCommand->exec();
            }
            pMainWindow->ui->MainDisplayWidget->mouseX=ints[0];
            pMainWindow->ui->MainDisplayWidget->mouseY=ints[1];
            pMainWindow->ui->MainDisplayWidget->update();
        }
            return GetNumber();
            break;
            default:return GetNumber();

        }
    }
};
#endif // ROTATESTATE_H
