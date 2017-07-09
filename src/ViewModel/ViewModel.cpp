//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include "../Common/BaseCommand.h"
#include "src/ViewModel/Commands/AddLineCommand.h"
#include "src/ViewModel/Commands/addellipsecommand.h"
#include "src/ViewModel/Commands/newcanvascommand.h"
#include "src/ViewModel/Commands/penupdatecommand.h"
#include <QPainter>
#include <QDebug>

const shared_ptr<BaseCommand> &ViewModel::getAddLineCommand() const {
    return addLineCommand;
}
const shared_ptr<BaseCommand> &ViewModel::getAddEllipseCommand() const{
    return addEllipseCommand;
}
const shared_ptr<BaseCommand> &ViewModel::getAddRectCommand() const{
    return addRectCommand;
}

const shared_ptr<BaseCommand> &ViewModel::getNewCanvasCommand() const {
    return newCanvasCommand;
}

const shared_ptr<BaseCommand> &ViewModel::getPenUpdateCommand() const {
    return penUpdateCommand;
}

void ViewModel::update(Params params) {
    switch (params.getType()) {
    case NOTIFY::UPDATE_IMAGE:
        RefreshDisplayImage();
        break;
    }
}

void ViewModel::RefreshDisplayImage() {
    if (layouts == nullptr)
        return;
    displayImage = QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32);
    QPainter painter(&displayImage);
    //painter.fillRect(QRectF(0,0,displayImage.width(),displayImage.height()),QColor(255,255,255));
    painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < layouts->list.size(); i++)
    {
        switch ((layouts->list)[i]->getType())
        {
        case SHAPE::LINE:
        {
            shared_ptr<Line> line = shared_ptr<Line>(static_pointer_cast<Line>((layouts->list)[i]));
            Pen linePen = line->getPen();
            QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
            tmpPen.setWidth(linePen.getLineWidth());
            qDebug()<<((line->getPosX() + line->getX1())*displayImage.width())<<((line->getPosY() + line->getY1())*displayImage.height())
                   <<((line->getPosX() + line->getX2())*displayImage.width())<<((line->getPosY() + line->getY2())*displayImage.height());
            painter.setPen(tmpPen);
            painter.drawLine((line->getPosX() + line->getX1())*displayImage.width(), (line->getPosY() + line->getY1())*displayImage.height(),
                             (line->getPosX() + line->getX2())*displayImage.width(), (line->getPosY() + line->getY2())*displayImage.height());
        }
            break;
        case SHAPE::ELLIPSE:
        {
            shared_ptr<Ellipse> ellipse = shared_ptr<Ellipse>(static_pointer_cast<Ellipse>((layouts->list)[i]));
            Pen ellipsePen = ellipse->getPen();
            Brush ellipseBrush = ellipse->getBrush();
            QPen tmpPen(QColor(ellipsePen.getForeR(),ellipsePen.getForeG(),ellipsePen.getForeB()));
            QBrush tmpBrush(QColor(ellipseBrush.getBackR(),ellipseBrush.getBackG(),ellipseBrush.getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(ellipsePen.getPenStyle()));
            tmpPen.setWidth(ellipsePen.getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(ellipseBrush.getBrushStyle()));
            painter.setPen(tmpPen);
            painter.setBrush(tmpBrush);
            painter.drawEllipse(QPoint((int)ellipse->getPosX(),(int)ellipse->getPosY()),(int)ellipse->getA(),(int)ellipse->getB());
        }
            break;
        case SHAPE::PIXMAP:
            break;
        case SHAPE::RECT:
            shared_ptr<Rect> rect = shared_ptr<Rect>(static_pointer_cast<Rect>((layouts->list)[i]));
            Pen rectPen = rect->getPen();
            QPen tmpPen(QColor(rectPen.getForeR(), rectPen.getForeG(), rectPen.getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(rectPen.getPenStyle()));
            tmpPen.setWidth(rectPen.getLineWidth());
            painter.setPen(tmpPen);
            painter.drawRect(QRectF((int)rect->getPosX(), (int)rect->getPosY(), (int)rect->getWidth(), (int)rect->getHeight()));
            break;

        }
    }
}

void ViewModel::NewCanvas(unsigned int width, unsigned int height)
{
    displayImage = QImage(QSize(width, height), QImage::Format_ARGB32);
    RefreshDisplayImage();
}

ViewModel::ViewModel(shared_ptr<Model> pModel) :
    addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand(pModel))),
    addEllipseCommand(shared_ptr<BaseCommand>(new AddEllipseCommand(pModel))),
    newCanvasCommand(shared_ptr<BaseCommand>(new NewCanvasCommand(pModel,shared_ptr<ViewModel>(this)))),
    penUpdateCommand(shared_ptr<BaseCommand>(new PenUpdateCommand(pModel)))
{
    displayImage = QImage(QSize(800, 600), QImage::Format_ARGB32);
    backGround=QImage(":/img/img/background.png");
}
