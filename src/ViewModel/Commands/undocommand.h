#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
class UndoCommand: public BaseCommand
{
public:
    UndoCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}
    void exec() {
        //vector<int> ints=params.getInts();
        //centerX,centerY,a,b
        pModel->undo();
    }
};
#endif // UNDOCOMMAND_H
