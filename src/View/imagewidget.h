#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "../Common/DataStructure.h"
#include "../Constants.h"
#include "../Common/BaseCommand.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);        //单击
    void mouseReleaseEvent(QMouseEvent *event);      //释放
    void mouseMoveEvent(QMouseEvent *event);         //移动
    void DrawTreeFromData(struct DrawData drawData, int margin, char *text=NULL);
    void paintUpdate(); //刷新
    void ClearImage();  //清空图片
     void SetImage(const QImage *image){this->image=image;update();}
    void SetPen(const Pen* pen){this->pen=pen;}
    void SetBrush(const Brush* brush){this->brush=brush;}
    void SetState(int *state){this->state=state;}
    void setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand){this->addLineCommand=addLineCommand;}
private:
   const QImage *image;
   const Pen* pen;
   const Brush* brush;
    int * state;
   shared_ptr<BaseCommand> addLineCommand;
   int mouseLastX,mouseLastY,mouseX,mouseY;

};

#endif // IMAGEWIDGET_H
