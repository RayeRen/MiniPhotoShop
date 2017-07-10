//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include "../Common/BaseCommand.h"
#include "src/ViewModel/Commands/AddLineCommand.h"
#include "src/ViewModel/Commands/addellipsecommand.h"
#include "src/ViewModel/Commands/addpiccommand.h"
#include "src/ViewModel/Commands/addrectcommand.h"
#include "src/ViewModel/Commands/newcanvascommand.h"
#include "src/ViewModel/Commands/penupdatecommand.h"
#include "src/ViewModel/Commands/brushupdatecommand.h"
#include "src/ViewModel/Commands/changedselectedcommand.h"
#include "src/ViewModel/Commands/layouttransformcommand.h"
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

    switch (params.getType()) {
    case NOTIFY::UPDATE_IMAGE:
    {
        vector<int> ints=params.getInts();
        //RefreshDisplayImage(ints[0]);

        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[ints[0]],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;

        qDebug()<<"UPDATE_IMAGE";
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({ints[0]});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);
    }
        break;
    case NOTIFY::UPDATE_IMAGE_ADD:
    {
        vector<int> ints=params.getInts();
        shared_ptr<QImage> pImage(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        displayBuffer.push_back(pImage);
        RefreshDisplayImage(ints[0]);
        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*pImage,QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::NEW_LAYOUT);
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);
    }


        break;
    case NOTIFY::ADD_IMAGE_FAILED:
        notify(params);
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
        QPen selectedRectPen(SETTINGS::SELETCED_RECT_COLOR);
        selectedRectPen.setStyle(SETTINGS::SELECTED_RETC_STYLE);
        selectedRectPen.setWidthF(SETTINGS::SELECTED_RECT_WIDTH);
        QBrush selectedBrush;
        selectedBrush.setStyle(Qt::NoBrush);

        QPainter painter(&(*displayBuffer[index]));
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(QRect(0,0,displayImage.width(),displayImage.height()),QColor(0,0,0,0));
        shared_ptr<BaseShape> baseShape=(layouts->list)[index];

        painter.translate(baseShape->getPosX(),baseShape->getPosY());


        painter.rotate(baseShape->getAngle());
        painter.scale(baseShape->getScaleX(),baseShape->getScaleY());
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

            painter.drawLine( line->getX1(),  line->getY1(),
                              line->getX2(),  line->getY2());
            if(index==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                int minX=(line->getX1()>line->getX2())?line->getX2():line->getX1();
                int minY=(line->getY1()>line->getY2())?line->getY2():line->getY1();
                painter.drawRect(QRect(minX-SETTINGS::SELECTED_RECT_BORDER,minY-SETTINGS::SELECTED_RECT_BORDER,
                                       std::abs(line->getX1()-line->getX2())+SETTINGS::SELECTED_RECT_BORDER,std::abs(line->getY1()-line->getY2())+SETTINGS::SELECTED_RECT_BORDER));
            }
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
            painter.drawEllipse(QPoint(0,0),ellipse->getA(),ellipse->getB());
            if(index==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                painter.drawRect(QRect(-ellipse->getA()-SETTINGS::SELECTED_RECT_BORDER,-ellipse->getB()-SETTINGS::SELECTED_RECT_BORDER,
                                       ellipse->getA()*2+SETTINGS::SELECTED_RECT_BORDER*2,ellipse->getB()*2+SETTINGS::SELECTED_RECT_BORDER*2));
            }
        }
            break;
        case SHAPE::PIXMAP:
        {
            shared_ptr<Pixmap> pixmap = shared_ptr<Pixmap>(static_pointer_cast<Pixmap>((layouts->list)[index]));
            painter.drawImage(QRectF(0,0,pixmap->GetWidth(),pixmap->GetHeight()),*(pixmap->Output()),QRectF(0,0,pixmap->GetWidth(),pixmap->GetHeight()));
            if(index==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                painter.drawRect(QRect(-SETTINGS::SELECTED_RECT_BORDER,-SETTINGS::SELECTED_RECT_BORDER,
                                       pixmap->GetWidth()+SETTINGS::SELECTED_RECT_BORDER*2, pixmap->GetHeight()+SETTINGS::SELECTED_RECT_BORDER*2));
            }
        }
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
            painter.drawRect(QRectF(0,0, rect->getWidth(),rect->getHeight()));
            if(index==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                painter.drawRect(QRect(-SETTINGS::SELECTED_RECT_BORDER,-SETTINGS::SELECTED_RECT_BORDER,
                                       rect->getWidth()+SETTINGS::SELECTED_RECT_BORDER*2, rect->getHeight()+SETTINGS::SELECTED_RECT_BORDER*2));
            }
            break;
        }
    }

    for(int i=0;i<displayBuffer.size();i++)
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[i],QRectF(0,0,displayImage.width(),displayImage.height()));
}

void ViewModel::NewCanvas(unsigned int width, unsigned int height)
{
    displayImage = QImage(QSize(width, height), QImage::Format_ARGB32);
    RefreshDisplayImage();
}

ViewModel::ViewModel(shared_ptr<Model> pModel) :
    addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand(pModel))),
    addPicCommand(shared_ptr<BaseCommand>(new AddPicCommand(pModel))),
    addEllipseCommand(shared_ptr<BaseCommand>(new AddEllipseCommand(pModel))),
    addRectCommand(shared_ptr<BaseCommand>(new AddRectCommand(pModel))),
    newCanvasCommand(shared_ptr<BaseCommand>(new NewCanvasCommand(pModel,shared_ptr<ViewModel>(this)))),
    changeSelectedCommand(shared_ptr<BaseCommand>(new ChangeSelectedCommand(pModel,shared_ptr<ViewModel>(this)))),
    layoutTransCommand(shared_ptr<BaseCommand>(new LayoutTransCommand(pModel,shared_ptr<ViewModel>(this)))),
    penUpdateCommand(shared_ptr<BaseCommand>(new PenUpdateCommand(pModel))),
    brushUpdateCommand(shared_ptr<BaseCommand>(new BrushUpdateCommand(pModel))),
    selectedLayout(-1)
{
    displayImage = QImage(QSize(800, 600), QImage::Format_ARGB32);
    backGround=QImage(":/img/img/background.png");
}

void ViewModel::SetSelectedLayout(int selectedLayout)
{
    int oldValue=this->selectedLayout;
    this->selectedLayout=selectedLayout;
    RefreshDisplayImage(oldValue);
    if(selectedLayout>=0)
        RefreshDisplayImage(selectedLayout);

    if(oldValue>=0)
    {
        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[oldValue],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({oldValue});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);
    }
    Params params;
    params.setType(NOTIFY::DISPLAY_REFRESH);
    notify(params);
}

void ViewModel::LayoutMove(int x,int y)
{
    if(selectedLayout>=0)
    {
        (layouts->list)[selectedLayout]->Move(x,y);
        RefreshDisplayImage(selectedLayout);

        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[selectedLayout],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({selectedLayout});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);

        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);
    }
    else
    {
        Params params;
        params.setType(NOTIFY::NO_LAYOUT_SELECTED);
        notify(params);
    }
}

void ViewModel::LayoutRotate(double angle)
{
    if(selectedLayout>=0)
    {
        (layouts->list)[selectedLayout]->Rotate(angle);
        RefreshDisplayImage(selectedLayout);

        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[selectedLayout],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({selectedLayout});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);

        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);
    }
    else
    {
        Params params;
        params.setType(NOTIFY::NO_LAYOUT_SELECTED);
        notify(params);
    }
}

void ViewModel::LayoutScale(double scaleX,double scaleY)
{
    if(selectedLayout>=0)
    {
        (layouts->list)[selectedLayout]->Scale(scaleX,scaleY);
        RefreshDisplayImage(selectedLayout);

        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[selectedLayout],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({selectedLayout});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);

        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);
    }
    else
    {
        Params params;
        params.setType(NOTIFY::NO_LAYOUT_SELECTED);
        notify(params);
    }
}
