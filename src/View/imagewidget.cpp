#include "imagewidget.h"
ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image=new QImage;
    canvasScale=1.0;
    realWidth=width();
    realHeight=height();
    setCursor(QCursor(Qt::CrossCursor));
    emit NewCanvasScale(canvasScale);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    if(image!=NULL&&!image->isNull())
        p.drawImage(QRectF((realWidth-(image->width())*canvasScale)/2,(realHeight-(image->height())*canvasScale)/2,image->width()*canvasScale,image->height()*canvasScale),*image,QRectF(0,0,image->width(),image->height()));
    StateManager::Run(EVENT::CANVAS_REPAINT);
    return;
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

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    emit CursorMove(event->localPos().x(),event->localPos().y());
    Params params;
    params.setInts({(int)event->localPos().x(),(int)event->localPos().y()});
    StateManager::Run(EVENT::MOUSE_LEFT_PRESSED,params);
    return;
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit CursorMove(-1,-1);
    StateManager::Run(EVENT::MOUSE_LEFT_RELEASED);
    return;
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit CursorMove(event->localPos().x(),event->localPos().y());
    Params params;
    params.setInts({(int)event->localPos().x(),(int)event->localPos().y()});
    StateManager::Run(EVENT::MOUSE_MOVE,params);
    return;
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    realWidth=event->size().width();
    realHeight=event->size().height();
}

void ImageWidget::wheelEvent(QWheelEvent *event)
{
    canvasScale*=event->delta()*SETTINGS::CANVAS_SCALE_STEP+1;
    emit NewCanvasScale(canvasScale);
    update();
}
