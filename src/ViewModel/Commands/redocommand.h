#ifndef REDOCOMMAND_H
#define REDOCOMMAND_H


#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"


class RedoCommand: public BaseCommand
{
public:
    RedoCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}
    void exec() {
        //vector<int> ints=params.getInts();
        //centerX,centerY,a,b
        pModel->redo();
    }
};

#endif // REDOCOMMAND_H
