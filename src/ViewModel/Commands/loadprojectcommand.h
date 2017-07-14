#ifndef LOADPROJECTCOMMAND_H
#define LOADPROJECTCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class LoadProjectCommand:public BaseCommand
{
public:
    LoadProjectCommand(const shared_ptr<Model> &pModel, const shared_ptr<ViewModel> &pViewModel):BaseCommand(pModel, pViewModel){}
    void exec(){
        string path(params.getStrings()[0]);
        pModel->loadProject(path);
    }
};

#endif // LOADPROJECTCOMMAND_H
