//
// Created by Raye on 2017/7/6.
//

#include "ViewModel.h"

const shared_ptr<BaseCommand> &ViewModel::getAddLineCommand() const {
    return addLineCommand;
}

void ViewModel::update(Params params) {

}
