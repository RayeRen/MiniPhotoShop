//
// Created by Raye on 2017/7/6.
//

#include "Model.h"

void Model::addLine(int centerX,int centerY,int x1,int y1,int x2,int y2)
{
    shared_ptr<Line> pLine;
    layouts.list.push_back(pLine=shared_ptr<Line>(new Line(centerX,
        centerY,SHAPE::LINE,string("Line"),1.0,1.0,0.0,pen,x1,y1,x2,y2)));

}

