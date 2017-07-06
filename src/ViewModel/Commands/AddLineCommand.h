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
        pModel->addLine();
    }
};


#endif //MINIPHOTOSHOP_ADDLINECOMMAND_H
