#ifndef LAYOUTORDERCHANGECOMMAND_H
#define LAYOUTORDERCHANGECOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
class LayoutOrderChangeCommand : public BaseCommand {
public:
    LayoutOrderChangeCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        //ints[0] -> before layout index  ints[1] -> after layout index
        // before -> after
        int type=params.getType();
        int selectedlayoutindex=pViewModel->GetSelectedLayout();
        int maxindex=pViewModel->GetMaxLayoutIndex();
        qDebug()<<"--------------LayoutOrderChange Begin-------------------";
        qDebug()<<"Type:"<<type<<"selectedLayoutIndex:"<<selectedlayoutindex<<"MaxIndex:"<<maxindex;
        switch(type){
        case COMMAND::LAYOUT_ORDER_DOWN:{
            //Layout 5 -> Layout 4
            if(selectedlayoutindex>=1){
                pModel->LayoutOrderChange(selectedlayoutindex,selectedlayoutindex-1);
                pViewModel->SetSelectedLayout(selectedlayoutindex-1);
            }
            //vector<int> ints=params.getInts();

        }
            break;
        case COMMAND::LAYOUT_ORDER_UP:{
            //Layout 5 -> Layout 6
            if(maxindex>=0&&selectedlayoutindex>=0){
                if(selectedlayoutindex<maxindex){
                    pModel->LayoutOrderChange(selectedlayoutindex,selectedlayoutindex+1);
                    pViewModel->SetSelectedLayout(selectedlayoutindex+1);
                }
            }
        }
            break;
        case COMMAND::LAYOUT_ORDER_CHANGE:{
            vector<int> ints=params.getInts();
            pModel->LayoutOrderChange(ints[0],ints[1]);
            pViewModel->SetSelectedLayout(ints[1]);
        }

            break;
        }
        qDebug()<<"--------------LayoutOrderChange End-------------------";


    }
};
#endif // LAYOUTORDERCHANGECOMMAND_H
