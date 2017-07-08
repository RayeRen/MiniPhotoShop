#include "imageWidget.h"
#include <qDebug>
ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image=new QImage;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    /*
    if(image!=NULL&&!image->isNull())
    {
        QRectF target,source(0,0,image->width(),image->height());
        float tmp;
        if(((float)width())/height()>((float)image->width())/image->height())
        {
            tmp=((float)height())/image->height();
            target.setRect(width()/2-image->width()/2*tmp,0,image->width()*tmp,height());
        }
        else
        {
            tmp=((float)width())/image->width();
            target.setRect(0,height()/2-image->height()/2*tmp,width(),image->height()*tmp);
        }

        p.drawImage(target,*image,source);
    }
*/
    if(image!=NULL&&!image->isNull())
    {
        p.drawImage(QRectF(0,0,width(),height()),*image,QRectF(0,0,image->width(),image->height()));
    }
    switch(*state)
    {
    case STATE::INIT:break;
    case STATE::DRAW_LINE:
        if(pen!=NULL)
        {
            QPen tmpPen(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(pen->getPenStyle()));
            tmpPen.setWidth(pen->getLineWidth());
            p.setPen(tmpPen);
            p.drawLine(mouseLastX,mouseLastY,mouseX,mouseY);
        }
        break;
    }
}

void ImageWidget::ClearImage()
{
    image=NULL;
    update();
}

void ImageWidget::paintUpdate()
{
    update();
}
/*
void imageWidget::DrawTreeFromData(struct DrawData drawData,int margin,char *text)
{
    delete image;
    image=new QImage(drawData.width+2*margin,drawData.height+2*margin,QImage::Format_RGB888);
    QColor color(255,255,255);
    image->fill(color);
    struct Line *p=drawData.lines;

    QPainter painter(image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(0,0,0));
    if(text!=NULL)
        painter.drawText(drawData.width/2,margin/3*2,text);
    while(p!=NULL)
    {
        painter.drawLine(p->x1+margin,p->y1+margin,p->x2+margin,p->y2+margin);
        p=p->next;
    }
    paintUpdate();
}
*/



void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    switch(*state)
    {
    case STATE::INIT:
        *state=STATE::DRAW_LINE;
        mouseX=mouseLastX=event->localPos().x();
        mouseY=mouseLastY=event->localPos().y();
        break;
    }
 update();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch(*state)
    {
       case STATE::DRAW_LINE:
         *state=STATE::INIT;
        Params para;
        int centerX=(mouseLastX+mouseX)/2,centerY=(mouseLastY+mouseY)/2;
        para.setInts({centerX,centerY,mouseLastX-centerX,mouseLastY-centerY,mouseX-centerX,mouseY-centerY});
        addLineCommand->setParams(para);
        addLineCommand->exec();
        qDebug()<<centerX<<centerY<<mouseLastX-centerX<<mouseLastY-centerY<<mouseX-centerX<<mouseY-centerY;
        break;

    }
     update();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseX=event->localPos().x();
    mouseY=event->localPos().y();
    update();
}
