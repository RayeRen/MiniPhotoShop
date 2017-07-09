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

    void ClearModel();
public:
    void addLine(){
    }
    void addLine(double centerX,double centerY,double x1,double y1,double x2,double y2);
    void addEllipse(double centerX,double centerY,double a,double b);//a -- x axis, b -- y axis
    void addRect(double centerX, double centerY, double width, double height);
    bool newProject(bool isSavedPre);
    bool saveProject(string path)const;
    bool loadProject(string path);
    void SetPen(Pen pen){this->pen=pen;}
    void SetPenColor(unsigned char r,unsigned char g,unsigned char b);
    void SetPenWidth(int newWidth){pen.setLineWidth(newWidth);}
    void SetPenStyle(int newStyle){pen.setPenStyle(newStyle);}
    void SetBrushColor(unsigned char r,unsigned char g,unsigned char b);
    void SetBrushStyle(int newStyle){brush.setBrushStyle(newStyle);}
    bool isProjectEmpty()const;
    const Brush* GetBrush(){return &brush;}
    const Pen* GetPen(){return &pen;}
    const Layouts* GetLayouts(){return &layouts;}
};


#endif //MINIPHOTOSHOP_MODEL_H
