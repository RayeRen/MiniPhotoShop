#ifndef LAYOUTTRANSFORMCOMMAND_H
#define LAYOUTTRANSFORMCOMMAND_H


#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class LayoutTransCommand : public BaseCommand {
public:
    LayoutTransCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        switch(params.getType())
        {
        case COMMAND::LAYOUT_MOVE:
        {
            vector<int> ints=params.getInts();
            pViewModel->LayoutMove(ints[0],ints[1]);
        }
            break;
        case COMMAND::LAYOUT_ROTATE:
        {
            vector<double> doubles=params.getDoubles();
            pViewModel->LayoutRotate(doubles[0]);
        }
            break;
        case COMMAND::LAYOUT_SCALE:
        {
            vector<double> doubles=params.getDoubles();
            pViewModel->LayoutScale(doubles[0],doubles[1]);
        }
            break;
        }
    }
};

#endif // LAYOUTTRANSFORMCOMMAND_H
