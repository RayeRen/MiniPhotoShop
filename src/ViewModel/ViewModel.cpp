//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include <QPainter>
const shared_ptr<BaseCommand> &ViewModel::getAddLineCommand() const {
    return addLineCommand;
}

void ViewModel::update(Params params) {

}
void ViewModel::RefreshDisplayImage()
{
    if(layouts==NULL)
        return;
    displayImage=QImage(QSize(displayImage.width(),displayImage.height()),QImage::Format_ARGB32);
    QPainter painter(&displayImage);
    for(int i=0;i<layouts->list.size();i++)
    {
        switch((layouts->list)[i]->getType())
        {
        case SHAPE::LINE:
        {
            shared_ptr<Line> line=shared_ptr<Line>(dynamic_pointer_cast<Line>((layouts->list)[i]));
            Pen linePen=line->getPen();
            QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
            tmpPen.setWidth(linePen.getLineWidth());
            painter.drawLine(line->getPosX()+line->getX1(),line->getPosX()+line->getY1(),line->getPosX()+line->getX2(),line->getPosY()+line->getY2());
        }
            break;
        case SHAPE::ELLIPSE:
            break;
        case SHAPE::PIXMAP:
            break;
        case SHAPE::RECT:
            break;

        }
    }
}
