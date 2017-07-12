#ifndef LAYOUTTRANSFORMFINISHCOMMAND_H
#define LAYOUTTRANSFORMFINISHCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
class LayoutTransNotifyCommand : public BaseCommand {
public:
    LayoutTransNotifyCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        qDebug()<<"Exec Change Notify";
        switch(params.getType())
        {
        case COMMAND::LAYOUT_CHANGEBEGIN:
        {
            qDebug()<<"Change begin";
            int layoutindex=pViewModel->GetSelectedLayout();
            if(layoutindex>=0){
                pModel->LayoutTransform(1, layoutindex);
            }
        }
            break;
        case COMMAND::LAYOUT_CHANGEEND:
        {
            qDebug()<<"Change end";
            int layoutindex=pViewModel->GetSelectedLayout();
            if(layoutindex>=0){
                pModel->LayoutTransform(0, layoutindex);
            }
        }
            break;
        }
    }
};
#endif // LAYOUTTRANSFORMFINISHCOMMAND_H
