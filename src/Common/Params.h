//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_PARAMS_H
#define MINIPHOTOSHOP_PARAMS_H

#include <vector>
#include <string>
#include <memory>

using namespace std;

class Params {
public:
    const vector<int> &getInts() const {
        return ints;
    }

    void setInts(const vector<int> &ints) {
        Params::ints = ints;
    }

    const vector<shared_ptr<void>> &getPtrs() const {
        return ptrs;
    }

    void setPtrs(const vector<shared_ptr<void>> &ptrs) {
        Params::ptrs = ptrs;
    }

    const vector<double> &getDoubles() const {
        return doubles;
    }

    void setDoubles(const vector<double> &doubles) {
        Params::doubles = doubles;
    }

    const vector<string> &getStrings() const {
        return strings;
    }

    void setStrings(const vector<string> &strings) {
        Params::strings = strings;
    }

    void setType(int type)
    {
        this->type=type;
    }

    int getType() const
    {
        return type;
    }

private:
    int type;
    vector<int> ints;

    vector<shared_ptr<void> > ptrs;

    vector<double> doubles;

    vector<string> strings;

};


#endif //MINIPHOTOSHOP_PARAMS_H
