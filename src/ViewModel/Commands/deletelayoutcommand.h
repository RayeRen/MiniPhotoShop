#ifndef DELETELAYOUT_H
#define DELETELAYOUT_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class DeleteLayoutCommand : public BaseCommand {
public:
    DeleteLayoutCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {

        qDebug()<<"exec delete layout command";
        int layoutindex=pViewModel->GetSelectedLayout();
        if(layoutindex>=0){
            pModel->DeleteLayout(layoutindex);
        }else{
            qDebug()<<"Cannot Remove Layout";
        }

    }
};
#endif // DELETELAYOUT_H
