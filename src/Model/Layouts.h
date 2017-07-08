#ifndef LAYOUTS_H
#define LAYOUTS_H

#include <vector>
#include <memory>
#include <src/Common/DataStructure.h>

using namespace std;

class LAYOUTS{
protected:
    vector<shared_ptr<BaseShape*>>list;
};

#endif // LAYOUTS_H
