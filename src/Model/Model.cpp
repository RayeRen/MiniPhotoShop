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
    params.setType(NOTIFY::UPDATE_IMAGE);
    notify(params);
}

