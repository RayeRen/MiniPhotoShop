//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"
#include "../Common/BaseCommand.h"
#include "src/ViewModel/Commands/AddLineCommand.h"
#include "src/ViewModel/Commands/addellipsecommand.h"
#include "src/ViewModel/Commands/addpiccommand.h"
#include "src/ViewModel/Commands/AddRectCommand.h"
#include "src/ViewModel/Commands/newcanvascommand.h"
#include "src/ViewModel/Commands/penupdatecommand.h"
#include "src/ViewModel/Commands/brushupdatecommand.h"
#include "src/ViewModel/Commands/undocommand.h"
#include "src/ViewModel/Commands/redocommand.h"
#include "src/ViewModel/Commands/changedselectedcommand.h"
#include "src/ViewModel/Commands/layouttransformcommand.h"
#include "src/ViewModel/Commands/layouttransformnotifycommand.h"
#include "src/ViewModel/Commands/newprojectcommand.h"
#include "src/ViewModel/Commands/loadprojectcommand.h"
#include "src/ViewModel/Commands/saveprojectcommand.h"
#include "src/ViewModel/Commands/deletelayoutcommand.h"
#include "src/ViewModel/Commands/saveaspicturecommand.h"
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
        RefreshDisplayImage(ints[0]);

        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[ints[0]],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);

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
        displayBuffer.insert(displayBuffer.begin()+ints[0],pImage);
        //displayBuffer.push_back(pImage);
        if(this->selectedLayout>=ints[0])
            this->selectedLayout++;
        qDebug()<<"Buffer Size:"<<displayBuffer.size();
        RefreshDisplayImage(ints[0]);
        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);
        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*pImage,QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::NEW_LAYOUT);
        newParams.setInts({ints[0]});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);
        break;
    }
    case NOTIFY::UPDATE_IMAGE_MINUS:{
        qDebug()<<"minus";
        vector<int> ints=params.getInts();
        qDebug()<<"Remove Minus:"<<ints[0];
        vector<shared_ptr<QImage>>::iterator it=displayBuffer.begin()+ints[0];
        displayBuffer.erase(it);
        if(this->selectedLayout>=ints[0])
            this->selectedLayout--;
        SetSelectedLayout(this->selectedLayout);
        qDebug()<<"Remove Refresh end";
        Params params;
        params.setType(NOTIFY::DISPLAY_REFRESH);
        notify(params);
        qDebug()<<"Message Display_refresh end";
        Params newParams;
        newParams.setType(NOTIFY::DELETE_LAYOUT);
        newParams.setInts({ints[0],this->selectedLayout});
        notify(newParams);
        qDebug()<<"Message Notify";
    }
        break;
    case NOTIFY::ADD_IMAGE_FAILED:
        notify(params);
        break;
    case NOTIFY::CLEAR:{
        qDebug()<<"clear view model";
        ClearViewModel();
        qDebug()<<"ok view model";
        Params newParams;
        newParams.setType(NOTIFY::CLEAR);
        notify(newParams);
    }
        break;
    }
}
void ViewModel::ClearViewModel(){
    this->selectedLayout=-1;
    displayBuffer.clear();
    RefreshDisplayImage();
}

void ViewModel::SaveAsPicture(string path)
{
    QImage outputImage=QImage(QSize(displayImage.width(),displayImage.height()),QImage::Format_ARGB32);
    QPainter painter(&outputImage);
    //painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRect(0,0,displayImage.width(),displayImage.height()),QColor(0,0,0,0));
    for(int i=0;i<displayBuffer.size();i++)
    {

        if(i==selectedLayout)
        {
            QImage tmpLayout=QImage(QSize(displayImage.width(),displayImage.height()),QImage::Format_ARGB32);
            QPainter layoutPainter(&tmpLayout);

           // layoutPainter.setCompositionMode(QPainter::CompositionMode_Source);
            layoutPainter.fillRect(QRect(0,0,displayImage.width(),displayImage.height()),Qt::transparent);
            shared_ptr<BaseShape> baseShape=(layouts->list)[i];

            layoutPainter.translate(baseShape->getPosX(),baseShape->getPosY());

            layoutPainter.rotate(baseShape->getAngle());
            layoutPainter.scale(baseShape->getScaleX(),baseShape->getScaleY());
            switch((layouts->list)[i]->getType())
            {
            case SHAPE::LINE:
            {
                shared_ptr<Line> line = shared_ptr<Line>(static_pointer_cast<Line>((layouts->list)[i]));
                Pen linePen = line->getPen();
                QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
                tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
                tmpPen.setWidth(linePen.getLineWidth());
                layoutPainter.setPen(tmpPen);
                layoutPainter.drawLine( line->getX1(),  line->getY1(),line->getX2(),  line->getY2());
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
                layoutPainter.setPen(tmpPen);
               layoutPainter.setBrush(tmpBrush);
                layoutPainter.drawEllipse(QPoint(0,0),ellipse->getA(),ellipse->getB());
            }
                break;
            case SHAPE::PIXMAP:
            {
                shared_ptr<Pixmap> pixmap = shared_ptr<Pixmap>(static_pointer_cast<Pixmap>((layouts->list)[i]));
                layoutPainter.drawImage(QRect(-((int)(pixmap->GetWidth()/2)),-((int)(pixmap->GetHeight()/2)),pixmap->GetWidth(),pixmap->GetHeight()),*(pixmap->Output()),QRect(0,0,pixmap->GetWidth(),pixmap->GetHeight()));
            }
                break;
            case SHAPE::RECT:
                shared_ptr<Rect> rect = shared_ptr<Rect>(static_pointer_cast<Rect>((layouts->list)[i]));
                Pen rectPen = rect->getPen();
                Brush rectBrush = rect->getBrush();
                QPen tmpPen(QColor(rectPen.getForeR(),rectPen.getForeG(),rectPen.getForeB()));
                QBrush tmpBrush(QColor(rectBrush.getBackR(),rectBrush.getBackG(),rectBrush.getBackB()));

                tmpPen.setStyle(static_cast<Qt::PenStyle>(rectPen.getPenStyle()));
                tmpPen.setWidth(rectPen.getLineWidth());
                tmpBrush.setStyle(static_cast<Qt::BrushStyle>(rectBrush.getBrushStyle()));
                layoutPainter.setPen(tmpPen);
                layoutPainter.setBrush(tmpBrush);
               layoutPainter.drawRect(QRectF(-rect->getWidth()/2,-rect->getHeight()/2, rect->getWidth(),rect->getHeight()));
                break;
            }
            painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),tmpLayout,QRectF(0,0,displayImage.width(),displayImage.height()));
            continue;
        }
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[i],QRectF(0,0,displayImage.width(),displayImage.height()));
    }
    outputImage.save(QString(path.c_str()));
}

void ViewModel::RefreshDisplayImage(int i)
{
    if (layouts == nullptr)
        return;
    qDebug()<<"RefreshDisplayImage"<<this->selectedLayout;
    displayImage = QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32);
    QPainter painter(&displayImage);
    // painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRectF(0,0,displayImage.width(),displayImage.height()),QColor(255,255,255));
    painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(i<0)
    {

    }
    else
    {
        QPen selectedRectPen(SETTINGS::SELETCED_RECT_COLOR);
        selectedRectPen.setStyle(SETTINGS::SELECTED_RETC_STYLE);
        selectedRectPen.setWidthF(SETTINGS::SELECTED_RECT_WIDTH);
        QBrush selectedBrush;
        selectedBrush.setStyle(Qt::NoBrush);

        QPainter painter(&(*displayBuffer[i]));
        painter.setCompositionMode(QPainter::CompositionMode_Source);

        painter.fillRect(QRect(0,0,displayImage.width(),displayImage.height()),QColor(0,0,0,0));
        shared_ptr<BaseShape> baseShape=(layouts->list)[i];
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.translate(baseShape->getPosX(),baseShape->getPosY());

        painter.rotate(baseShape->getAngle());
        painter.scale(baseShape->getScaleX(),baseShape->getScaleY());
        switch((layouts->list)[i]->getType())
        {
        case SHAPE::LINE:
        {
            shared_ptr<Line> line = shared_ptr<Line>(static_pointer_cast<Line>((layouts->list)[i]));
            Pen linePen = line->getPen();
            QPen tmpPen(QColor(linePen.getForeR(),linePen.getForeG(),linePen.getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(linePen.getPenStyle()));
            tmpPen.setWidth(linePen.getLineWidth());
            painter.setPen(tmpPen);

            painter.drawLine( line->getX1(),  line->getY1(),
                              line->getX2(),  line->getY2());
            if(i==selectedLayout)
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
            painter.drawEllipse(QPoint(0,0),ellipse->getA(),ellipse->getB());
            if(i==selectedLayout)
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
            shared_ptr<Pixmap> pixmap = shared_ptr<Pixmap>(static_pointer_cast<Pixmap>((layouts->list)[i]));
            painter.drawImage(QRect(-((int)(pixmap->GetWidth()/2)),-((int)(pixmap->GetHeight()/2)),pixmap->GetWidth(),pixmap->GetHeight()),*(pixmap->Output()),QRect(0,0,pixmap->GetWidth(),pixmap->GetHeight()));
            if(i==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                painter.drawRect(QRect(-SETTINGS::SELECTED_RECT_BORDER-pixmap->GetWidth()/2,-SETTINGS::SELECTED_RECT_BORDER-pixmap->GetHeight()/2,
                                       pixmap->GetWidth()+SETTINGS::SELECTED_RECT_BORDER*2, pixmap->GetHeight()+SETTINGS::SELECTED_RECT_BORDER*2));
            }
        }
            break;
        case SHAPE::RECT:
            shared_ptr<Rect> rect = shared_ptr<Rect>(static_pointer_cast<Rect>((layouts->list)[i]));
            Pen rectPen = rect->getPen();
            Brush rectBrush = rect->getBrush();
            QPen tmpPen(QColor(rectPen.getForeR(),rectPen.getForeG(),rectPen.getForeB()));
            QBrush tmpBrush(QColor(rectBrush.getBackR(),rectBrush.getBackG(),rectBrush.getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(rectPen.getPenStyle()));
            tmpPen.setWidth(rectPen.getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(rectBrush.getBrushStyle()));
            painter.setPen(tmpPen);
            painter.setBrush(tmpBrush);
            painter.drawRect(QRectF(-rect->getWidth()/2,-rect->getHeight()/2, rect->getWidth(),rect->getHeight()));
            if(i==selectedLayout)
            {
                painter.setPen(selectedRectPen);
                painter.setBrush(selectedBrush);
                painter.drawRect(QRect(-SETTINGS::SELECTED_RECT_BORDER-rect->getWidth()/2,-SETTINGS::SELECTED_RECT_BORDER-rect->getHeight()/2,
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
    layoutTransNotifyCommand(shared_ptr<BaseCommand>(new LayoutTransNotifyCommand(pModel,shared_ptr<ViewModel>(this)))),

    penUpdateCommand(shared_ptr<BaseCommand>(new PenUpdateCommand(pModel))),
    brushUpdateCommand(shared_ptr<BaseCommand>(new BrushUpdateCommand(pModel))),
    newProjectCommand(shared_ptr<BaseCommand>(new NewProjectCommand(pModel))),
    loadProjectCommand(shared_ptr<BaseCommand>(new LoadProjectCommand(pModel))),
    saveProjectCommand(shared_ptr<BaseCommand>(new SaveProjectCommand(pModel))),
    undoCommand(shared_ptr<BaseCommand>(new UndoCommand(pModel))),
    redoCommand(shared_ptr<BaseCommand>(new RedoCommand(pModel))),
    deleteLayoutCommand(shared_ptr<BaseCommand>(new DeleteLayoutCommand(pModel,shared_ptr<ViewModel>(this)))),
    saveAsPictureCommand(shared_ptr<BaseCommand>(new SaveAsPictureCommand(pModel,shared_ptr<ViewModel>(this)))),
    selectedLayout(-1)
{
    displayImage = QImage(QSize(200, 200), QImage::Format_ARGB32);
    backGround=QImage(":/img/img/background.png");
}

void ViewModel::SetSelectedLayout(int selectedLayout)
{
    int oldValue=this->selectedLayout;
    this->selectedLayout=selectedLayout;
    qDebug()<<"Refresh"<<oldValue;
    RefreshDisplayImage(oldValue);
    qDebug()<<"Refresh2:"<<selectedLayout;
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
    if(selectedLayout>=0){
        shared_ptr<QImage> preview(new QImage(QSize(displayImage.width(), displayImage.height()), QImage::Format_ARGB32));
        QPainter painter(&(*preview));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),backGround,QRectF(0,0,displayImage.width(),displayImage.height()));
        painter.drawImage(QRectF(0,0,displayImage.width(),displayImage.height()),*displayBuffer[selectedLayout],QRectF(0,0,displayImage.width(),displayImage.height()));
        Params newParams;
        newParams.setType(NOTIFY::REFRESH_PREVIEW);
        newParams.setInts({selectedLayout});
        newParams.setPtrs({shared_ptr<void>(preview)});
        notify(newParams);
    }
    qDebug()<<"Where is the bug";
    Params params;
    params.setType(NOTIFY::DISPLAY_REFRESH);
    notify(params);
    int pixmapflag=0;
    if(this->selectedLayout>=0){
        if( (layouts->list)[this->selectedLayout]->getType()==SHAPE::PIXMAP){
            pixmapflag=1;
        }
    }
    Params newparams;
    newparams.setType(NOTIFY::IF_LAYOUT_PIXMAP);
    newparams.setInts({pixmapflag});
    notify(newparams);

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
