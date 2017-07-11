#ifndef PIXMAPFILTERCOMMAND_H
#define PIXMAPFILTERCOMMAND_H

#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"
class PixmapFilterCommand : public BaseCommand {
public:
    PixmapFilterCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {
        qDebug()<<"Exec Pixmap Filter";
        Params params;
        pModel->PixmapFilter(params);
    }
};
#endif // PIXMAPFILTERCOMMAND_H
