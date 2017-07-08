#ifndef LAYOUTS_H
#define LAYOUTS_H

#include <vector>
#include <memory>
#include <src/Common/DataStructure.h>

using namespace std;

class Layouts{
protected:
    vector<shared_ptr<BaseShape>>list;

public:
    friend class Model;
    friend class ViewModel;
};

#endif // LAYOUTS_H
