#ifndef LAYOUTTRANSFORMCOMMAND_H
#define LAYOUTTRANSFORMCOMMAND_H

class LayoutTransCommand : public BaseCommand {
public:
    LayoutTransCommand(const shared_ptr<Model> &pModel,const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

    void exec() {

    }
};

#endif // LAYOUTTRANSFORMCOMMAND_H
