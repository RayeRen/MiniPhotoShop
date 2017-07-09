#ifndef SAVEPROJECTCOMMAND_H
#define SAVEPROJECTCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class SaveProjectCommand:public BaseCommand
{
public:
    SaveProjectCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}

    bool exec(string path)
    {
        return pModel->saveProject(path);
    }
};

#endif // SAVEPROJECTCOMMAND_H
