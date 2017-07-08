#ifndef LAYOUTS_H
#define LAYOUTS_H

#include <vector>
#include <memory>
#include <src/Common/DataStructure.h>

using namespace std;

class Layouts{
protected:
    vector<shared_ptr<BaseShape>>list;

<<<<<<< HEAD
public:

=======
    friend class Model;
    friend class ViewModel;
>>>>>>> 30b55d7c48bd4d84ac2a52ce3d8dd362dca6ac05
};

#endif // LAYOUTS_H
