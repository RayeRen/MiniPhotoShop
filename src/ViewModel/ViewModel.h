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

    const shared_ptr<BaseCommand> &getNewCanvasCommand() const;
    const shared_ptr<BaseCommand> &getPenUpdateCommand() const;
    virtual void update(Params params);
    void SetLayouts(const Layouts* layouts){this->layouts=layouts;}
    const QImage* GetDisplayImage(){return &displayImage;}
    void RefreshDisplayImage(int index=-1);
    void NewCanvas(unsigned int width,unsigned int height);
    void SetSelectedLayout(int selectedLayout){this->selectedLayout=selectedLayout;}
    int GetSelectedLayout(){return selectedLayout;}
    ViewModel(shared_ptr<Model> pModel);
private:
    shared_ptr<BaseCommand> addLineCommand,addEllipseCommand,addRectCommand,newCanvasCommand,penUpdateCommand;
    vector<QImage> displayBuffer;
    QImage displayImage;
    const Layouts* layouts;
    QImage backGround;
    int selectedLayout;
//    ViewModel(){};

//    void operator = (const ViewModel& viewModel){}
};


#endif //MINIPHOTOSHOP_VIEWMODEL_H
