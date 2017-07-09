//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include "../Common/BaseCommand.h"
#include "src/ViewModel/Commands/AddLineCommand.h"
#include "src/ViewModel/Commands/addellipsecommand.h"
#include "src/ViewModel/Commands/addrectcommand.h"
#include "src/ViewModel/Commands/newcanvascommand.h"
#include "src/ViewModel/Commands/penupdatecommand.h"
#include "src/ViewModel/Commands/brushupdatecommand.h"
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

const shared_ptr<BaseCommand> &ViewModel::getNewProjectCommand() const
{
    return newProjectCommand;
}

const shared_ptr<BaseCommand> &ViewModel::getsaveProjectCommand() const
{
    return saveProjectCommand;
}

const shared_ptr<BaseCommand> &ViewModel::getloadProjectCommand() const
{
    return loadProjectCommand;
}

void ViewModel::update(Params params) {
    vector<int> ints=params.getInts();
    switch (params.getType()) {
    case NOTIFY::UPDATE_IMAGE:
        RefreshDisplayImage(ints[0]);
        break;
    case NOTIFY::UPDATE_IMAGE_ADD:
        displayBuffer.push_back(QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        RefreshDisplayImage(ints[0]);
        break;
    }
}

void ViewModel::RefreshDisplayImage(int index) {
    if (layouts == nullptr)
        return;
    displayImage = QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32);
    QPainter painter(&displayImage);
    painter.fillRect(QRectF(0,0,displayImage.width(),displayImage.height()),QColor(255,255,255));
    painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(index<0)
    {

    }
    else
    {
        QPainter painter(&displayBuffer[index]);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(0,0,displayImage.width(),displayImage.height()),QColor(0,0,0,0));

        switch((layouts->list)[index]->getType())
        {
        case SHAPE::LINE:
        {
            shared_ptr<Line> line = shared_ptr<Line>(static_pointer_cast<Line>((layouts->list)[index]));
            Pen linePen = line->getPen();
            QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
            tmpPen.setWidth(linePen.getLineWidth());
            painter.setPen(tmpPen);
            painter.drawLine(line->getPosX() + line->getX1(), line->getPosY() + line->getY1(),
                             line->getPosX() + line->getX2(), line->getPosY() + line->getY2());
        }
            break;
        case SHAPE::ELLIPSE:
        {
            shared_ptr<Ellipse> ellipse = shared_ptr<Ellipse>(static_pointer_cast<Ellipse>((layouts->list)[index]));
            Pen ellipsePen = ellipse->getPen();
            Brush ellipseBrush = ellipse->getBrush();
            QPen tmpPen(QColor(ellipsePen.getForeR(),ellipsePen.getForeG(),ellipsePen.getForeB()));
            QBrush tmpBrush(QColor(ellipseBrush.getBackR(),ellipseBrush.getBackG(),ellipseBrush.getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(ellipsePen.getPenStyle()));
            tmpPen.setWidth(ellipsePen.getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(ellipseBrush.getBrushStyle()));
            painter.setPen(tmpPen);
            painter.setBrush(tmpBrush);
            painter.drawEllipse(QPoint(ellipse->getPosX(),ellipse->getPosY()),ellipse->getA(),ellipse->getB());
        }
            break;
        case SHAPE::PIXMAP:
            break;
        case SHAPE::RECT:
            shared_ptr<Rect> rect = shared_ptr<Rect>(static_pointer_cast<Rect>((layouts->list)[index]));
            Pen rectPen = rect->getPen();
            Brush rectBrush = rect->getBrush();
            QPen tmpPen(QColor(rectPen.getForeR(),rectPen.getForeG(),rectPen.getForeB()));
            QBrush tmpBrush(QColor(rectBrush.getBackR(),rectBrush.getBackG(),rectBrush.getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(rectPen.getPenStyle()));
            tmpPen.setWidth(rectPen.getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(rectBrush.getBrushStyle()));
            painter.setPen(tmpPen);
            painter.setBrush(tmpBrush);
            painter.drawRect(QRectF(rect->getPosX(), rect->getPosY(), rect->getWidth(),rect->getHeight()));
            break;
        }
    }
    for(int i=0;i<displayBuffer.size();i++)
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),displayBuffer[i],QRectF(0,0,displayImage.width(),displayImage.height()));
}

void ViewModel::NewCanvas(unsigned int width, unsigned int height)
{
    displayImage = QImage(QSize(width, height), QImage::Format_ARGB32);
    RefreshDisplayImage();
}

ViewModel::ViewModel(shared_ptr<Model> pModel) :
    addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand(pModel))),
    addEllipseCommand(shared_ptr<BaseCommand>(new AddEllipseCommand(pModel))),
    addRectCommand(shared_ptr<BaseCommand>(new AddRectCommand(pModel))),
    newCanvasCommand(shared_ptr<BaseCommand>(new NewCanvasCommand(pModel,shared_ptr<ViewModel>(this)))),
    penUpdateCommand(shared_ptr<BaseCommand>(new PenUpdateCommand(pModel))),
    brushUpdateCommand(shared_ptr<BaseCommand>(new BrushUpdateCommand(pModel))),
    selectedLayout(-1)
{
    displayImage = QImage(QSize(800, 600), QImage::Format_ARGB32);
    backGround=QImage(":/img/img/background.png");
}
