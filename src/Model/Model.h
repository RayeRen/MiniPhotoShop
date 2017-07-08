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
    void addRect(double centerX, double centerY, double width, double height);
    void SetPen(Pen pen){this->pen=pen;}
    void SetPenColor(unsigned char r,unsigned char g,unsigned char b);
    const Pen* GetPen(){return &pen;}
    const Layouts* GetLayouts(){return &layouts;}
};


#endif //MINIPHOTOSHOP_MODEL_H
