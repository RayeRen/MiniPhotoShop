#ifndef NEWPROJECTCOMMAND_H
#define NEWPROJECTCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class NewProjectCommand:public BaseCommand
{
public:
    NewProjectCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}
    void exec(){

    }

    bool exec(bool isSavedPre)
    {
        if(pModel->isProjectEmpty())
            return true;
        return pModel->newProject(isSavedPre);
    }
};

#endif // NEWPROJECTCOMMAND_H
