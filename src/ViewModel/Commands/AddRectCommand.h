#ifndef ADDRECCOMMAND_H
#define ADDRECCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class AddRectCommand:public BaseCommand
{
public:
    AddRectCommand(const shared_ptr<Model> *pModel):BaseCommand(pModel){}
    void exec()
    {
        vector<double> doubles=params.getDoubles();
        pModel->addRect(doubles[0],doubles[1],doubles[2],doubles[3]);
    }
};

#endif // ADDRECCOMMAND_H
