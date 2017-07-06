//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_BASECOMMAND_H
#define MINIPHOTOSHOP_BASECOMMAND_H


#include "Params.h"
#include "../Model/Model.h"

class BaseCommand {
public:
    BaseCommand(const shared_ptr<Model> &pModel) : pModel(pModel) {}

    void setParams(const Params &params) {
        BaseCommand::params = params;
    }

    virtual void exec() = 0;

protected:
    Params params;
    shared_ptr<Model> pModel;
};


#endif //MINIPHOTOSHOP_BASECOMMAND_H
