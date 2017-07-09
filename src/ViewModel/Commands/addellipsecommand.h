//
// Created by jzh on 2017/7/8.
//
#ifndef ADDELLIPSECOMMAND_H
#define ADDELLIPSECOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"


class AddEllipseCommand: public BaseCommand
{
public:
    AddEllipseCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}
    void exec() {
        vector<int> ints=params.getInts();
        //centerX,centerY,a,b
        pModel->addEllipse(ints[0],ints[1],ints[2],ints[3]);
    }
};

#endif // ADDELLIPSECOMMAND_H
