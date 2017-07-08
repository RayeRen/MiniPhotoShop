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
        vector<double> doubles=params.getDoubles();
        pModel->addLine(doubles[0],doubles[1],doubles[2],doubles[3],doubles[4],doubles[5]);
    }
};


#endif //MINIPHOTOSHOP_ADDLINECOMMAND_H
