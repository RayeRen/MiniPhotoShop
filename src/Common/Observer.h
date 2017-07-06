//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_OBSERVER_H
#define MINIPHOTOSHOP_OBSERVER_H


#include "Params.h"

class Observer {
public:
    virtual void update(Params params) = 0;
};

#endif //MINIPHOTOSHOP_OBSERVER_H
