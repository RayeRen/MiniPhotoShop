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
    ViewModel() : addLineCommand(shared_ptr<BaseCommand>(new AddLineCommand())) {}

    const shared_ptr<BaseCommand> &getAddLineCommand() const;

private:
    shared_ptr<BaseCommand> addLineCommand;
};


#endif //MINIPHOTOSHOP_VIEWMODEL_H
