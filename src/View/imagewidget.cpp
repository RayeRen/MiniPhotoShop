#include "imageWidget.h"
#include <qDebug>
#include <cmath>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image=new QImage;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
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
        qDebug()<<"Width"<<realWidth<<image->width();
        qDebug()<<"Height"<<realHeight<<image->height();
        p.drawImage(QRectF(0,0,realWidth,realHeight),*image,QRectF(0,0,image->width(),image->height()));
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
    case STATE::DRAW_ELLIPSE:
        if(pen!=NULL)
        {
            QPen tmpPen(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(pen->getPenStyle()));
            tmpPen.setWidth(pen->getLineWidth());
            p.setPen(tmpPen);
            p.drawEllipse(QPoint(mouseLastX,mouseLastY),std::abs(mouseX-mouseLastX),std::abs(mouseY-mouseLastY));
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
    case STATE::DRAW_LINE_INIT:
       *state=STATE::DRAW_LINE;
       emit StateChanged();
        //*state=STATE::DRAW_ELLIPSE;
        mouseX=mouseLastX=event->localPos().x();
        mouseY=mouseLastY=event->localPos().y();
        break;
    case STATE::DRAW_ELLIPSE_INIT:
        *state=STATE::DRAW_ELLIPSE;
        emit StateChanged();
         //*state=STATE::DRAW_ELLIPSE;
         mouseX=mouseLastX=event->localPos().x();
         mouseY=mouseLastY=event->localPos().y();
         break;
    }
    update();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int centerX,centerY;
    Params para;
    switch(*state)
    {
    case STATE::DRAW_LINE:
        *state=STATE::INIT;
        emit StateChanged();
        //Params para;
        qDebug()<<mouseX<<mouseY<<mouseLastX<<mouseLastY;
        centerX=(mouseLastX+mouseX)/2,centerY=(mouseLastY+mouseY)/2;
        para.setDoubles({(double)centerX/realWidth,(double)centerY/realHeight,(double)(mouseLastX-centerX)/realWidth,
                         (double)(mouseLastY-centerY)/realHeight,(double)(mouseX-centerX)/realWidth,
                         (double)(mouseY-centerY)/realHeight});
        addLineCommand->setParams(para);
        addLineCommand->exec();
        break;
    case STATE::DRAW_ELLIPSE:
        *state=STATE::INIT;
        emit StateChanged();
        centerX=mouseLastX,centerY=mouseLastY;
        para.setDoubles({(double)centerX,(double)centerY,(double)(std::abs(mouseX-mouseLastX)),(double)(std::abs(mouseY-mouseLastY))});
        addEllipseCommand->setParams(para);
        addEllipseCommand->exec();
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

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    realWidth=event->size().width();
    realHeight=event->size().height();
    if(newCanvasCommand!=nullptr)
    {
        Params params;
        params.setInts({realWidth,realHeight});
        newCanvasCommand->setParams(params);
        newCanvasCommand->exec();
    }

}
