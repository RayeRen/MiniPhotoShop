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
        vector<double> doubles=params.getDoubles();
        //centerX,centerY,a,b
        pModel->addEllipse(doubles[0],doubles[1],doubles[2],doubles[3]);
    }
};

#endif // ADDELLIPSECOMMAND_H
