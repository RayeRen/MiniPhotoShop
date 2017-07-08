#ifndef NEWCANVASCOMMAND_H
#define NEWCANVASCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
#include "../../ViewModel/ViewModel.h"

class NewCanvasCommand:public BaseCommand
{
public:
    NewCanvasCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec()
    {
        vector<int> ints=params.getInts();
     pViewModel->NewCanvas(ints[0],ints[1]);
    }
};

#endif // NEWCANVASCOMMAND_H
