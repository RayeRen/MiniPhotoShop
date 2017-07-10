//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_VIEWMODEL_H
#define MINIPHOTOSHOP_VIEWMODEL_H

#include <memory>
#include <QImage>
#include "src/Common/Observable.h"
#include "src/Model/Model.h"

using namespace std;

class BaseCommand;

class ViewModel : public Observable,
                  public Observer {
public:
//    static ViewModel& getInstance(shared_ptr<Model> pModel){
//        static ViewModel instance(pModel);
//        return instance;
//    }

    const shared_ptr<BaseCommand> &getAddLineCommand() const;
    const shared_ptr<BaseCommand> &getAddEllipseCommand() const;
    const shared_ptr<BaseCommand> &getAddRectCommand() const;
    const shared_ptr<BaseCommand> &getAddPicCommand() const{return addPicCommand;}
    const shared_ptr<BaseCommand> &getNewCanvasCommand() const;
    const shared_ptr<BaseCommand> &getPenUpdateCommand() const;
    const shared_ptr<BaseCommand> &getNewProjectCommand() const;
    const shared_ptr<BaseCommand> &getsaveProjectCommand() const;
    const shared_ptr<BaseCommand> &getloadProjectCommand() const;
    const shared_ptr<BaseCommand> &getBrushUpdateCommand() const{return brushUpdateCommand;}
    const shared_ptr<BaseCommand> &getRedoCommand() const{return redoCommand;}
    const shared_ptr<BaseCommand> &getUndoCommand() const{return undoCommand;}
    const shared_ptr<BaseCommand> &getChangeSelectedCommand() const{return changeSelectedCommand;}
     const shared_ptr<BaseCommand> &getLayoutTransCommand() const{return layoutTransCommand;}

    virtual void update(Params params);



    void SetLayouts(const Layouts* layouts){this->layouts=layouts;}
    const QImage* GetDisplayImage(){return &displayImage;}
    void RefreshDisplayImage(int index=-1);
    void NewCanvas(unsigned int width,unsigned int height);
    void SetSelectedLayout(int selectedLayout);
    int GetSelectedLayout(){return selectedLayout;}
    void SetPen(const Pen* pen){this->pen=pen;}
    void SetBrush(const Brush* brush){this->brush=brush;}
    void LayoutMove(int x,int y);
    void LayoutRotate(double angle);
    void LayoutScale(double scaleX,double scaleY);
    const Pen* GetPen(){return pen;}
    const Brush* GetBrush(){return brush;}
    ViewModel(shared_ptr<Model> pModel);
private:
    shared_ptr<BaseCommand> addLineCommand,addEllipseCommand,
    addRectCommand,newCanvasCommand,penUpdateCommand,brushUpdateCommand,
    newProjectCommand,saveProjectCommand,loadProjectCommand,changeSelectedCommand,
    addPicCommand,layoutTransCommand,undoCommand,redoCommand
    ;
    vector<shared_ptr<QImage>> displayBuffer;
    QImage displayImage;
    const Layouts* layouts;
    QImage backGround;
    int selectedLayout;
    const Pen* pen;
    const Brush* brush;
//    ViewModel(){};

//    void operator = (const ViewModel& viewModel){}
};


#endif //MINIPHOTOSHOP_VIEWMODEL_H
