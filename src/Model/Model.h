//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_MODEL_H
#define MINIPHOTOSHOP_MODEL_H


#include "../Common/Observable.h"
#include "../Common/DataStructure.h"
class Model : public Observable {
    Pen pen;
    Brush brush;
public:
    void addLine(){
    }
    void SetPen(Pen pen){this->pen=pen;}
    const Pen* GetPen(){return &pen;}
};


#endif //MINIPHOTOSHOP_MODEL_H
