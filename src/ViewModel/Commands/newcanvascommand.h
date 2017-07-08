#ifndef NEWCANVASCOMMAND_H
#define NEWCANVASCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class NewCanvasCommand:public BaseCommand
{
public:
    NewCanvasCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel);

    void exec();

};

#endif // NEWCANVASCOMMAND_H
