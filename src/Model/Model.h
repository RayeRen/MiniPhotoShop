//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_MODEL_H
#define MINIPHOTOSHOP_MODEL_H


#include "../Common/Observable.h"
#include "../Common/DataStructure.h"
#include "Layouts.h"

class Model : public Observable {
    Pen pen;
    Brush brush;
    Layouts layouts;
public:
    void addLine(int centerX,int centerY,int x1,int y1,int x2,int y2);
    void SetPen(Pen pen){this->pen=pen;}
    const Pen* GetPen(){return &pen;}
    const Layouts* GetLayouts(){return &layouts;}
};


#endif //MINIPHOTOSHOP_MODEL_H
