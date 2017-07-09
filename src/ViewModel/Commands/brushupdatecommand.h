#ifndef BRUSHUPDATECOMMAND_H
#define BRUSHUPDATECOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class BrushUpdateCommand : public BaseCommand {
public:
    BrushUpdateCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}

    void exec() {
        vector<int> ints=params.getInts();
        switch(params.getType())
        {
        case COMMAND::UPDATE_BRUSH_COLOR:
            pModel->SetBrushColor(static_cast<unsigned char>(ints[0]),static_cast<unsigned char>(ints[1]),
                    static_cast<unsigned char>(ints[2]));
            break;
         case COMMAND::UPDATE_BRUSH_STYLE:
            pModel->SetBrushStyle(ints[0]);
            break;
        }


    }
};
#endif // BRUSHUPDATECOMMAND_H
