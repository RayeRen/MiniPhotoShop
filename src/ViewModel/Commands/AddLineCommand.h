//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_ADDLINECOMMAND_H
#define MINIPHOTOSHOP_ADDLINECOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class AddLineCommand : public BaseCommand {
public:
    AddLineCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}

    void exec() {
        vector<int> ints=params.getInts();
        pModel->addLine(ints[0],ints[1],ints[2],ints[3],ints[4],ints[5]);
    }
};


#endif //MINIPHOTOSHOP_ADDLINECOMMAND_H
