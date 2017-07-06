//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_OBSERVABLE_H
#define MINIPHOTOSHOP_OBSERVABLE_H

#include <memory>
#include "Params.h"
#include "Observer.h"

using namespace std;

class Observable {
protected:
    vector<shared_ptr<Observer>> observers;
public:
    void addObserver(shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void removeObserver(shared_ptr<Observer> dObserver) {
        for (auto it = observers.begin(); it != observers.end();) {
            if (*it == dObserver) {
                it = observers.erase(it);
            } else {
                it++;
            }
        }
    }

    void notify(Params params) {
        for (const auto &observer:observers) {
            observer->update(params);
        }
    }
};


#endif //MINIPHOTOSHOP_OBSERVABLE_H
