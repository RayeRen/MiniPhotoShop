#ifndef SAVEASPICTURECOMMAND_H
#define SAVEASPICTURECOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class SaveAsPictureCommand : public BaseCommand {
public:
    SaveAsPictureCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        string path(params.getStrings()[0]);
        pViewModel->SaveAsPicture(path);
    }
};
#endif // SAVEASPICTURECOMMAND_H
