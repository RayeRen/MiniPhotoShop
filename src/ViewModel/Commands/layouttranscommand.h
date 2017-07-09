#ifndef LAYOUTTRANSCOMMAND_H
#define LAYOUTTRANSCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class LayoutTransCommand : public BaseCommand {
public:
    LayoutTransCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        vector<int> ints=params.getInts();
        pViewModel->SetSelectedLayout(ints[0]);
    }
};

#endif //LAYOUTTRANSCOMMAND_H
