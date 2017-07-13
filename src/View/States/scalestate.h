#ifndef SCALESTATE_H
#define SCALESTATE_H
#include "BaseState.h"
class ScaleState:public BaseState
{
public:
    ScaleState():BaseState(STATE::SCALE){}
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
            pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以开始缩放图层 ")));
            pMainWindow->ui->MainDisplayWidget->update();
        }
        return STATE::SCALE_INIT;
        break;
        case EVENT::MOUSE_MOVE:
        {
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            vector<int> ints=params.getInts();

            {
                Params params;
                params.setType(COMMAND::LAYOUT_SCALE);
                params.setDoubles({(double)(ints[0]-pMainWindow->ui->MainDisplayWidget->mouseX)*SETTINGS::SCALE_STEP+1,
                                (double)(ints[1]-pMainWindow->ui->MainDisplayWidget->mouseY)*SETTINGS::SCALE_STEP+1});

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
#endif // SCALESTATE_H
