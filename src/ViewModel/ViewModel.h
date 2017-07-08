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
    ViewModel(shared_ptr<Model> pModel);

    const shared_ptr<BaseCommand> &getAddLineCommand() const;
const shared_ptr<BaseCommand> &getNewCanvasCommand() const;
    virtual void update(Params params);
    void SetLayouts(const Layouts* layouts){this->layouts=layouts;}
    const QImage* GetDisplayImage(){return &displayImage;}
    void RefreshDisplayImage();
    void NewCanvas(unsigned int width,unsigned int height);
private:
    shared_ptr<BaseCommand> addLineCommand,newCanvasCommand;
    vector<shared_ptr<QImage>> displayBuffer;
    QImage displayImage;
    const Layouts* layouts;
};


#endif //MINIPHOTOSHOP_VIEWMODEL_H
