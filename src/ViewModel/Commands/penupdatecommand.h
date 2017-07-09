#ifndef PENUPDATECOMMAND_H
#define PENUPDATECOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class PenUpdateCommand : public BaseCommand {
public:
    PenUpdateCommand(const shared_ptr<Model> &pModel) : BaseCommand(pModel) {}

    void exec() {
        vector<int> ints=params.getInts();
        switch(params.getType())
        {
        case COMMAND::UPDATE_PEN_COLOR:
            pModel->SetPenColor(static_cast<unsigned char>(ints[0]),static_cast<unsigned char>(ints[1]),
                    static_cast<unsigned char>(ints[2]));
            break;
         case COMMAND::UPDATE_PEN_WIDTH:
            pModel->SetPenWidth(ints[0]);
            break;
         case COMMAND::UPDATE_PEN_STYLE:
            pModel->SetPenStyle(ints[0]);
            break;
        }


    }
};

#endif // PENUPDATECOMMAND_H
