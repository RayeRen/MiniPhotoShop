#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
//Undo
class UndoCommand: public BaseCommand
{
public:
    UndoCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}
    void exec() {
        pModel->undo();
    }
};
#endif // UNDOCOMMAND_H
