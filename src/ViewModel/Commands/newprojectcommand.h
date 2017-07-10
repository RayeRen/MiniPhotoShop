#ifndef NEWPROJECTCOMMAND_H
#define NEWPROJECTCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class NewProjectCommand:public BaseCommand
{
public:
    NewProjectCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}

    void exec()
    {
        if(!pModel->isProjectEmpty())
            pModel->newProject();
    }
};

#endif // NEWPROJECTCOMMAND_H
