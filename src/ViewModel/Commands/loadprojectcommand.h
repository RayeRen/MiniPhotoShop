#ifndef LOADPROJECTCOMMAND_H
#define LOADPROJECTCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class LoadProjectCommand:public BaseCommand
{
public:
    LoadProjectCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}

    bool exec(string path)
    {
        return pModel->loadProject(path);
    }
};

#endif // LOADPROJECTCOMMAND_H
