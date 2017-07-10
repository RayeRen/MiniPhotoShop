#ifndef ADDPICCOMMAND_H
#define ADDPICCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"


class AddPicCommand: public BaseCommand
{
public:
    AddPicCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}
    void exec() {
        vector<string> strings=params.getStrings();
        //centerX,centerY,a,b
        pModel->addImage(strings[0]);
    }
};

#endif // ADDPICCOMMAND_H
