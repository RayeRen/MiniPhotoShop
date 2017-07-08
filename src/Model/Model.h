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
    Layouts layouts;
public:
    void addLine(){
    }
    void addLine(double centerX,double centerY,double x1,double y1,double x2,double y2);
    void addEllipse(double centerX,double centerY,double a,double b);//a -- x axis, b -- y axis
    void SetPen(Pen pen){this->pen=pen;}
<<<<<<< HEAD
    const Pen* GetPen()const{return &pen;}
=======
    void SetPenColor(unsigned char r,unsigned char g,unsigned char b);
    const Pen* GetPen(){return &pen;}
    const Layouts* GetLayouts(){return &layouts;}
>>>>>>> 30b55d7c48bd4d84ac2a52ce3d8dd362dca6ac05
};


#endif //MINIPHOTOSHOP_MODEL_H
