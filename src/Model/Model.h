//
// Created by Raye on 2017/7/6.
//

#ifndef MINIPHOTOSHOP_MODEL_H
#define MINIPHOTOSHOP_MODEL_H


#include "../Common/Observable.h"
#include "../Common/DataStructure.h"
#include "Layouts.h"

class Model : public Observable {
private:
    Pen pen;
    Brush brush;
    Model(){}
    Model(const Model & model){}
    void operator = (const Model& model){}
    Layouts layouts;
public:
    static Model& getInstance(){
        static Model instance;
        return instance;
    }
    void addLine(){
    }
    void addLine(int centerX,int centerY,int x1,int y1,int x2,int y2);
    void SetPen(Pen pen){this->pen=pen;}
    const Pen* GetPen(){return &pen;}
    const Layouts* GetLayouts(){return &layouts;}
};


#endif //MINIPHOTOSHOP_MODEL_H
