//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include "../Common/BaseCommand.h"
#include "src/ViewModel/Commands/AddLineCommand.h"
#include "src/ViewModel/Commands/newcanvascommand.h"
#include <QPainter>

const shared_ptr<BaseCommand> &ViewModel::getAddLineCommand() const {
    return addLineCommand;
}

const shared_ptr<BaseCommand> &ViewModel::getNewCanvasCommand() const {
    return newCanvasCommand;
}

void ViewModel::update(Params params) {
    switch (params.getType()) {
        case NOTIFY::UPDATE_IMAGE:
            RefreshDisplayImage();
            break;
    }
}

void ViewModel::RefreshDisplayImage() {
    if (layouts == NULL)
        return;
    displayImage = QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32);
    QPainter painter(&displayImage);
    for (int i = 0; i < layouts->list.size(); i++) {
        switch ((layouts->list)[i]->getType()) {
            case SHAPE::LINE: {
                shared_ptr<Line> line = shared_ptr<Line>(static_pointer_cast<Line>((layouts->list)[i]));
                Pen linePen = line->getPen();
                QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
                tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
                tmpPen.setWidth(linePen.getLineWidth());
               // QPen pen(Qt::red);
              //  pen.setStyle(Qt::SolidLine);
                painter.setPen(tmpPen);
                painter.drawLine((line->getPosX() + line->getX1())*displayImage.width(), (line->getPosY() + line->getY1())*displayImage.height(),
                                 (line->getPosX() + line->getX2())*displayImage.width(), (line->getPosY() + line->getY2())*displayImage.height());
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

void ViewModel::NewCanvas(unsigned int width, unsigned int height) {
    displayImage = QImage(QSize(width, height), QImage::Format_ARGB32);
    RefreshDisplayImage();
}

ViewModel::ViewModel(shared_ptr<Model> pModel) :
        addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand(pModel))),
        newCanvasCommand(shared_ptr<BaseCommand>(new NewCanvasCommand(pModel,shared_ptr<ViewModel>(this)))) {
    displayImage = QImage(QSize(800, 600), QImage::Format_ARGB32);
}
