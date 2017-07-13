#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "../Common/DataStructure.h"
#include "../Constants.h"
#include "../Common/BaseCommand.h"
#include "statemanager.h"
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);        //单击
    void mouseReleaseEvent(QMouseEvent *event);      //释放
    void mouseMoveEvent(QMouseEvent *event);         //移动
    void wheelEvent(QWheelEvent *event);
    void paintUpdate(); //刷新
    void ClearImage();  //清空图片
    void SetImage(const QImage *image){this->image=image;update();}
    void SetPen(const Pen* pen){this->pen=pen;}
    void SetBrush(const Brush* brush){this->brush=brush;}
    void setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand){this->addLineCommand=addLineCommand;}
    void setAddEllipseCommand(const shared_ptr<BaseCommand> &addEllipseCommand){this->addEllipseCommand=addEllipseCommand;}
    void setAddRectCommand(const shared_ptr<BaseCommand> &addRectCommand){this->addRectCommand=addRectCommand;}
    void setNewCanvasCommand(const shared_ptr<BaseCommand> &newCanvasCommand){this->newCanvasCommand=newCanvasCommand;}
    void setLayoutTransCommand(const shared_ptr<BaseCommand> &layoutTransCommand){this->layoutTransCommand=layoutTransCommand;}
    void setLayoutTransNotifyCommand(const shared_ptr<BaseCommand> &layoutTransNotifyCommand){this->layoutTransNotifyCommand=layoutTransNotifyCommand;}
    int getRealWidth() const{return realWidth;}
    int getRealHeight() const {return realHeight;}
    int getCanvasWidth() const {if(image!=NULL) return image->width();return 0;}
    int getCanvasHeight() const {if(image!=NULL) return image->height();return 0;}
    int getMouseSkewX() const{if(image!=NULL) return (realWidth-(image->width())*canvasScale)/2;return 0;}
    int getMouseSkewY() const{if(image!=NULL) return (realHeight-(image->height())*canvasScale)/2;return 0;}
    double getCanvasScale() const{return canvasScale;}
private:

   const QImage *image;
   const Pen* pen;
   const Brush* brush;
   double canvasScale;
   shared_ptr<BaseCommand> addLineCommand;
   shared_ptr<BaseCommand> addEllipseCommand;
   shared_ptr<BaseCommand> newCanvasCommand;
   shared_ptr<BaseCommand> addRectCommand;
   shared_ptr<BaseCommand> layoutTransCommand;
   shared_ptr<BaseCommand> layoutTransNotifyCommand;

   int mouseLastX,mouseLastY,mouseX,mouseY;
   int realWidth,realHeight;

friend class BaseState;
friend class DrawLineInitState;
friend class DrawLineState;
friend class DrawEllipseInitState;
friend class DrawEllipseState;
friend class DrawRectInitState;
friend class DrawRectState;
friend class MoveInitState;
friend class MoveState;
friend class ScaleInitState;
friend class ScaleState;
friend class RotateInitState;
friend class RotateState;
friend class StateCommonAction;
signals:
    void StateChanged();
    void CursorMove(int,int);
    void NewCanvasScale(double);
};

#endif // IMAGEWIDGET_H
