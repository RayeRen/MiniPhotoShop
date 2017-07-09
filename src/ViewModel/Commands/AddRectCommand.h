#ifndef ADDRECCOMMAND_H
#define ADDRECCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class AddRectCommand:public BaseCommand
{
public:
    AddRectCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}
    void exec()
    {
        vector<int> ints=params.getInts();
        pModel->addRect(ints[0],ints[1],ints[2],ints[3]);
    }
};

#endif // ADDRECCOMMAND_H
