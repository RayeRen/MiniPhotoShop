#ifndef DRAWLINESTATE_H
#define DRAWLINESTATE_H

#include "BaseState.h"

class DrawLineState:public BaseState
{
public:
    DrawLineState():BaseState(STATE::DRAW_LINE){}
    virtual int Process(int event, Params params)
    {
        qDebug()<<"CANVAS_DRAWLINE_BEGIN";
        switch(event)
        {
        case EVENT::ACTION_TRIGGERED:
            return StateCommonAction::ActionTrigged(GetNumber(),params);
            break;
        case EVENT::CANVAS_REPAINT:
        {
            qDebug()<<"CANVAS_DRAWLINE_BEGIN";
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            QPainter p(pMainWindow->ui->MainDisplayWidget);
            p.setRenderHint(QPainter::Antialiasing, true);
            if(pMainWindow->ui->MainDisplayWidget->pen!=NULL)
            {
                QPen tmpPen(QColor(pMainWindow->ui->MainDisplayWidget->pen->getForeR(),
                                   pMainWindow->ui->MainDisplayWidget->pen->getForeG(),
                                   pMainWindow->ui->MainDisplayWidget->pen->getForeB()));
                tmpPen.setStyle(static_cast<Qt::PenStyle>(pMainWindow->ui->MainDisplayWidget->pen->getPenStyle()));
                tmpPen.setWidth(pMainWindow->ui->MainDisplayWidget->pen->getLineWidth()*pMainWindow->ui->MainDisplayWidget->getCanvasScale());
                p.setPen(tmpPen);
                p.drawLine(pMainWindow->ui->MainDisplayWidget->mouseLastX
                           ,pMainWindow->ui->MainDisplayWidget->mouseLastY,
                           pMainWindow->ui->MainDisplayWidget->mouseX,pMainWindow->ui->MainDisplayWidget->mouseY);
            }
        }
            return GetNumber();
            break;
         case EVENT::MOUSE_LEFT_RELEASED:
        {
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            int centerX,centerY;
            Params para;
            centerX=(pMainWindow->ui->MainDisplayWidget->mouseLastX+pMainWindow->ui->MainDisplayWidget->mouseX)/2,
                    centerY=(pMainWindow->ui->MainDisplayWidget->mouseLastY+pMainWindow->ui->MainDisplayWidget->mouseY)/2;
            para.setInts({(int)((centerX-pMainWindow->ui->MainDisplayWidget->getMouseSkewX())/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                          (int)((centerY-pMainWindow->ui->MainDisplayWidget->getMouseSkewY())/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                          (int)((pMainWindow->ui->MainDisplayWidget->mouseLastX-centerX)/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                          (int)((pMainWindow->ui->MainDisplayWidget->mouseLastY-centerY)/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                         (int)((pMainWindow->ui->MainDisplayWidget->mouseX-centerX)/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                         (int)((pMainWindow->ui->MainDisplayWidget->mouseY-centerY)/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                          });
            pMainWindow->ui->MainDisplayWidget->addLineCommand->setParams(para);
           pMainWindow->ui->MainDisplayWidget-> addLineCommand->exec();
            pMainWindow->UpdateStatusBarInfo(QStringLiteral("请按下鼠标以确定直线的起点"));
             pMainWindow->ui->MainDisplayWidget->update();
        }
            return STATE::DRAW_LINE_INIT;
            break;
        case EVENT::MOUSE_MOVE:
        {
            MainWindow* pMainWindow=StateManager::GetpMainWindow();
            vector<int> ints=params.getInts();
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

#endif // DRAWLINESTATE_H
