//
// Created by Raye on 2017/7/6.
//

#include "Model.h"
#include <QDebug>
void Model::addLine(double centerX,double centerY,double x1,double y1,double x2,double y2)
{
    shared_ptr<Line> pLine;
    layouts.list.push_back(pLine=shared_ptr<Line>(new Line(centerX,
        centerY,SHAPE::LINE,string("Line"),1.0,1.0,0.0,pen,x1,y1,x2,y2)));
    qDebug()<<centerX<<centerY<<x1<<y1<<x2<<y2;
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
    params.setInts({layouts.list.size()-1});
    notify(params);
}
void Model::addEllipse(double centerX,double centerY,double a,double b){
    shared_ptr<Ellipse> pEllipse;
    layouts.list.push_back(pEllipse=shared_ptr<Ellipse>(new Ellipse(centerX,
        centerY,SHAPE::ELLIPSE,string("Ellipse"),1.0,1.0,0.0,pen,brush,a,b)));
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
     params.setInts({layouts.list.size()-1});
    notify(params);
}

void Model::addRect(double centerX, double centerY, double width, double height)
{
    shared_ptr<Rect> pRect;
    layouts.list.push_back(pRect = shared_ptr<Rect>(new Rect(centerX,
         centerY, SHAPE::RECT, string("Rectangle"),1.0,1.0,0,pen,brush,width,height)));
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
 params.setInts({layouts.list.size()-1});
    notify(params);
}

 void Model::SetPenColor(unsigned char r,unsigned char g,unsigned char b)
 {
     pen.setForeR(r);
     pen.setForeG(g);
     pen.setForeB(b);
 }

 void Model::SetBrushColor(unsigned char r,unsigned char g,unsigned char b)
 {
     brush.setBackR(r);
     brush.setBackG(g);
     brush.setBackB(b);
 }
