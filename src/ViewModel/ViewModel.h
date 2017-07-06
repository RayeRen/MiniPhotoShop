//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_VIEWMODEL_H
#define MINIPHOTOSHOP_VIEWMODEL_H

#include <memory>
#include "../Common/BaseCommand.h"
#include "Commands/AddLineCommand.h"

using namespace std;

class ViewModel : public Observable,
                  public Observer {
public:
    ViewModel(shared_ptr<Model> pModel) :
            addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand(pModel))) {}

    const shared_ptr<BaseCommand> &getAddLineCommand() const;

    virtual void update(Params params);

private:
    shared_ptr<BaseCommand> addLineCommand;
};


#endif //MINIPHOTOSHOP_VIEWMODEL_H
