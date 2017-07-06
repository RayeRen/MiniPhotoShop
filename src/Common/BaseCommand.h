//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_BASECOMMAND_H
#define MINIPHOTOSHOP_BASECOMMAND_H


#include "Params.h"

class BaseCommand {
public:
    void setParams(const Params &params) {
        BaseCommand::params = params;
    }

    virtual void exec() = 0;

protected:
    Params params;
};


#endif //MINIPHOTOSHOP_BASECOMMAND_H
