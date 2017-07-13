#ifndef ADDRECTSTATE_H
#define ADDRECTSTATE_H
#include "BaseState.h"
class DrawRectState:public BaseState
{
public:
   DrawRectState():BaseState(STATE::DRAW_RECT){}
    virtual int Process(int event, Params params)
    {
       switch(event)
       {
       case EVENT::ACTION_TRIGGERED:
           return StateCommonAction::ActionTrigged(GetNumber(),params);
           break;
       case EVENT::CANVAS_REPAINT:
       {
           MainWindow* pMainWindow=StateManager::GetpMainWindow();
           QPainter p(pMainWindow->ui->MainDisplayWidget);
           p.setRenderHint(QPainter::Antialiasing, true);
           if(pMainWindow->ui->MainDisplayWidget->pen!=NULL&&pMainWindow->ui->MainDisplayWidget->brush!=NULL)
           {
               QPen tmpPen(QColor(pMainWindow->ui->MainDisplayWidget->pen->getForeR(),
                                  pMainWindow->ui->MainDisplayWidget->pen->getForeG(),
                                  pMainWindow->ui->MainDisplayWidget->pen->getForeB()));
               QBrush tmpBrush(QColor(pMainWindow->ui->MainDisplayWidget->brush->getBackR(),
                                      pMainWindow->ui->MainDisplayWidget->brush->getBackG(),
                                      pMainWindow->ui->MainDisplayWidget->brush->getBackB()));

               tmpPen.setStyle(static_cast<Qt::PenStyle>(pMainWindow->ui->MainDisplayWidget->pen->getPenStyle()));
               tmpPen.setWidth(pMainWindow->ui->MainDisplayWidget->pen->getLineWidth()*pMainWindow->ui->MainDisplayWidget->getCanvasScale());
               tmpBrush.setStyle(static_cast<Qt::BrushStyle>(pMainWindow->ui->MainDisplayWidget->brush->getBrushStyle()));
               p.setPen(tmpPen);
               p.setBrush(tmpBrush);
               p.drawRect(pMainWindow->ui->MainDisplayWidget->mouseLastX,
                          pMainWindow->ui->MainDisplayWidget->mouseLastY,
                          pMainWindow->ui->MainDisplayWidget->mouseX-pMainWindow->ui->MainDisplayWidget->mouseLastX,
                          pMainWindow->ui->MainDisplayWidget->mouseY-pMainWindow->ui->MainDisplayWidget->mouseLastY);

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
                        (int)(std::abs(pMainWindow->ui->MainDisplayWidget->mouseX-pMainWindow->ui->MainDisplayWidget->mouseLastX)/pMainWindow->ui->MainDisplayWidget->getCanvasScale()),
                        (int)(std::abs(pMainWindow->ui->MainDisplayWidget->mouseY-pMainWindow->ui->MainDisplayWidget->mouseLastY)/pMainWindow->ui->MainDisplayWidget->getCanvasScale())});
          pMainWindow->ui->MainDisplayWidget->addRectCommand->setParams(para);
          pMainWindow->ui->MainDisplayWidget->addRectCommand->exec();

          pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定矩形的第一个顶点 ")));
      pMainWindow->ui->MainDisplayWidget->update();
       }
          return STATE::DRAW_RECT_INIT;
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
#endif // ADDRECTSTATE_H
