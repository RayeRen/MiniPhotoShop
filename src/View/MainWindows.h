//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_WINDOWS_H
#define MINIPHOTOSHOP_WINDOWS_H


#include "../Common/Observer.h"
#include "../Common/BaseCommand.h"

class MainWindows : public Observer {
public:
    void setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand);

    virtual void update(Params params);

private:
    shared_ptr<BaseCommand> addLineCommand;
};


#endif //MINIPHOTOSHOP_WINDOWS_H
