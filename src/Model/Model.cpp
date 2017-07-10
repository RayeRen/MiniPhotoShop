//
// Created by Raye on 2017/7/6.
//

#include "Model.h"
#include <QDebug>
#include <iostream>
#include <fstream>
Model::Model(){
    NowDoneIndex=-1;
    MaxDoneIndex=-1;
}

void Model::addLine(double centerX,double centerY,double x1,double y1,double x2,double y2)
{
    shared_ptr<Line> pLine;
    layouts.list.push_back(pLine=shared_ptr<Line>(new Line(centerX,
        centerY,SHAPE::LINE,string("Line"),1.0,1.0,0.0,pen,x1,y1,x2,y2)));
    qDebug()<<centerX<<centerY<<x1<<y1<<x2<<y2;
    addDoneEvent(COMMAND::CREATE,layouts.list.size()-1,shared_ptr<BaseShape>(new Line(*pLine)));
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
    params.setInts({(int)layouts.list.size()-1});
    notify(params);
}
void Model::addEllipse(double centerX,double centerY,double a,double b){
    shared_ptr<Ellipse> pEllipse;
    layouts.list.push_back(pEllipse=shared_ptr<Ellipse>(new Ellipse(centerX,
        centerY,SHAPE::ELLIPSE,string("Ellipse"),1.0,1.0,0.0,pen,brush,a,b)));
    addDoneEvent(COMMAND::CREATE,layouts.list.size()-1,shared_ptr<BaseShape>(new Ellipse(*pEllipse)));

    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
     params.setInts({(int)layouts.list.size()-1});
    notify(params);
}

void Model::addRect(double centerX, double centerY, double width, double height)
{
    shared_ptr<Rect> pRect;
    layouts.list.push_back(pRect = shared_ptr<Rect>(new Rect(centerX,
         centerY, SHAPE::RECT, string("Rectangle"),1.0,1.0,0,pen,brush,width,height)));
    addDoneEvent(COMMAND::CREATE,layouts.list.size()-1,shared_ptr<BaseShape>(new Rect(*pRect)));

    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
    params.setInts({(int)layouts.list.size()-1});
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

 void Model::ClearModel()
 {
     if(!layouts.list.empty())
     {
         layouts.list.clear();
     }
 }

 bool Model::isProjectEmpty()const
 {
     return layouts.list.empty();
 }

 void Model::newProject()
 {
     if(!isProjectEmpty())
         ClearModel();
 }

 void Model::saveProject(string path)const
 {
     fstream out;
     int i;
     int num = layouts.list.capacity() - 1;

     out.open(path, ios::out | ios::binary);
     if(!out)
     {
         return;
     }

     string head("This is a mpsd project file");
     out.write(head.c_str(), head.size());
     for(i = 0; i < num; i++)
     {
         int type = layouts.list[i]->getType();
         out.write(reinterpret_cast<char*>(&type), sizeof(int));
         switch(type)
         {
         case SHAPE::LINE:
         {
             shared_ptr<Line> line;
             line = shared_ptr<Line>(static_pointer_cast<Line>(layouts.list[i]));
             //BaseShape Data
             int PosX, PosY;
             double ScaleX, ScaleY, Angle;
             PosX = line->getPosX();
             PosY = line->getPosY();
             ScaleX = line->getScaleX();
             ScaleY = line->getScaleY();
             Angle = line->getAngle();
             out.write(reinterpret_cast<char*>(&PosX), sizeof(int));
             out.write(reinterpret_cast<char*>(&PosY), sizeof(int));
             out.write(reinterpret_cast<char*>(&ScaleX), sizeof(double));
             out.write(reinterpret_cast<char*>(&ScaleY), sizeof(double));
             out.write(reinterpret_cast<char*>(&Angle), sizeof(double));

             //Line Pen
             Pen pen;
             unsigned char R, G, B;
             int LineWidth;
             int PenStyle;
             pen = line->getPen();
             R = pen.getForeR();
             G = pen.getForeG();
             B = pen.getForeB();
             LineWidth = pen.getLineWidth();
             PenStyle = pen.getPenStyle();
             out.write(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&LineWidth), sizeof(int));
             out.write(reinterpret_cast<char*>(&PenStyle), sizeof(int));

             //Line Coordinates
             int X1, Y1, X2, Y2;
             X1 = line->getX1();
             Y1 = line->getY1();
             X2 = line->getX2();
             Y2 = line->getY2();
             out.write(reinterpret_cast<char*>(&X1), sizeof(int));
             out.write(reinterpret_cast<char*>(&Y1), sizeof(int));
             out.write(reinterpret_cast<char*>(&X2), sizeof(int));
             out.write(reinterpret_cast<char*>(&Y2), sizeof(int));
             break;
        }

         case SHAPE::ELLIPSE:
         {
             shared_ptr<Ellipse> ellipse;
             ellipse = shared_ptr<Ellipse>(static_pointer_cast<Ellipse>(layouts.list[i]));
             //BaseShape Data
             int PosX, PosY;
             double ScaleX, ScaleY, Angle;
             PosX = ellipse->getPosX();
             PosY = ellipse->getPosY();
             ScaleX = ellipse->getScaleX();
             ScaleY = ellipse->getScaleY();
             Angle = ellipse->getAngle();
             out.write(reinterpret_cast<char*>(&PosX), sizeof(int));
             out.write(reinterpret_cast<char*>(&PosY), sizeof(int));
             out.write(reinterpret_cast<char*>(&ScaleX), sizeof(double));
             out.write(reinterpret_cast<char*>(&ScaleY), sizeof(double));
             out.write(reinterpret_cast<char*>(&Angle), sizeof(double));

             //Ellipse Pen
             Pen pen;
             unsigned char R, G, B;
             int LineWidth;
             int PenStyle;
             pen = ellipse->getPen();
             R = pen.getForeR();
             G = pen.getForeG();
             B = pen.getForeB();
             LineWidth = pen.getLineWidth();
             PenStyle = pen.getPenStyle();
             out.write(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&LineWidth), sizeof(int));
             out.write(reinterpret_cast<char*>(&PenStyle), sizeof(int));

             //Ellipse Brush
             Brush brush;
             int BrushStyle;
             brush = ellipse->getBrush();
             R = brush.getBackR();
             G = brush.getBackG();
             B = brush.getBackB();
             BrushStyle = brush.getBrushStyle();
             out.write(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&BrushStyle), sizeof(int));

             //Ellipse Coordinates
             int a, b;
             a = ellipse->getA();
             b = ellipse->getB();
             out.write(reinterpret_cast<char*>(&a), sizeof(int));
             out.write(reinterpret_cast<char*>(&b), sizeof(int));
             break;
         }

         case SHAPE::RECT:
         {
             shared_ptr<Rect> rect;
             rect = shared_ptr<Rect>(static_pointer_cast<Rect>(layouts.list[i]));
             //BaseShape Data
             int PosX, PosY;
             double ScaleX, ScaleY, Angle;
             PosX = rect->getPosX();
             PosY = rect->getPosY();
             ScaleX = rect->getScaleX();
             ScaleY = rect->getScaleY();
             Angle = rect->getAngle();
             out.write(reinterpret_cast<char*>(&PosX), sizeof(int));
             out.write(reinterpret_cast<char*>(&PosY), sizeof(int));
             out.write(reinterpret_cast<char*>(&ScaleX), sizeof(double));
             out.write(reinterpret_cast<char*>(&ScaleY), sizeof(double));
             out.write(reinterpret_cast<char*>(&Angle), sizeof(double));

             //Rectangle Pen
             Pen pen;
             unsigned char R, G, B;
             int LineWidth;
             int PenStyle;
             pen = rect->getPen();
             R = pen.getForeR();
             G = pen.getForeG();
             B = pen.getForeB();
             LineWidth = pen.getLineWidth();
             PenStyle = pen.getPenStyle();
             out.write(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&LineWidth), sizeof(int));
             out.write(reinterpret_cast<char*>(&PenStyle), sizeof(int));

             //Rectangle Brush
             Brush brush;
             int BrushStyle;
             brush = rect->getBrush();
             R = brush.getBackR();
             G = brush.getBackG();
             B = brush.getBackB();
             BrushStyle = brush.getBrushStyle();
             out.write(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             out.write(reinterpret_cast<char*>(&BrushStyle), sizeof(int));

             //Rectangle Coordinates
             int Width, Height;
             Width = rect->getWidth();
             Height = rect->getHeight();
             out.write(reinterpret_cast<char*>(&Width), sizeof(int));
             out.write(reinterpret_cast<char*>(&Height), sizeof(int));
             break;
         }
         case SHAPE::PIXMAP:
             break;
         }
     }

     out.close();
 }

 void Model::loadProject(string path)
 {
     fstream in;
     int type;
     char head[30];
     int PosX, PosY, x1, y1, x2, y2, a, b, width, height, penStyle, lineWidth, brushstyle;
     unsigned char R, G, B;
     double scaleX, scaleY, angle;

     if(!isProjectEmpty())
         ClearModel();

     in.open(path, ios::in | ios::binary);
     if(!in)
         return;

     in.read(head, sizeof("This is a mpsd project file"));
     if(strcmp(head, "This is a mpsd project file") != 0)
         return;

     while(!in.eof())
     {
         in.read(reinterpret_cast<char*>(&type), sizeof(int));
         switch(type)
         {
         case SHAPE::LINE:
         {
             //BaseShape Data
             in.read(reinterpret_cast<char*>(&PosX), sizeof(int));
             in.read(reinterpret_cast<char*>(&PosY), sizeof(int));
             in.read(reinterpret_cast<char*>(&scaleX), sizeof(double));
             in.read(reinterpret_cast<char*>(&scaleY), sizeof(double));
             in.read(reinterpret_cast<char*>(&angle), sizeof(double));

             //Line Pen
             in.read(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&lineWidth), sizeof(int));
             in.read(reinterpret_cast<char*>(&penStyle), sizeof(int));
             //Set Pen
             Pen pen;
             pen.setForeR(R);
             pen.setForeG(G);
             pen.setForeB(B);
             pen.setLineWidth(lineWidth);
             pen.setPenStyle(penStyle);

             //Line Coordinates
             in.read(reinterpret_cast<char*>(&x1), sizeof(int));
             in.read(reinterpret_cast<char*>(&y1), sizeof(int));
             in.read(reinterpret_cast<char*>(&x2), sizeof(int));
             in.read(reinterpret_cast<char*>(&y2), sizeof(int));

             //New Layout
             shared_ptr<Line> pLine;
             layouts.list.push_back(pLine=shared_ptr<Line>(new Line(PosX,
                 PosY,SHAPE::LINE,string("Line"),scaleX,scaleY,angle,pen,x1,y1,x2,y2)));
             Params params;
             params.setType(NOTIFY::UPDATE_IMAGE_ADD);
             params.setInts({(int)layouts.list.size()-1});
             notify(params);
             break;
        }
         case SHAPE::ELLIPSE:
         {
             //BaseShape Data
             in.read(reinterpret_cast<char*>(&PosX), sizeof(int));
             in.read(reinterpret_cast<char*>(&PosY), sizeof(int));
             in.read(reinterpret_cast<char*>(&scaleX), sizeof(double));
             in.read(reinterpret_cast<char*>(&scaleY), sizeof(double));
             in.read(reinterpret_cast<char*>(&angle), sizeof(double));

             //Ellipse Pen
             in.read(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&lineWidth), sizeof(int));
             in.read(reinterpret_cast<char*>(&penStyle), sizeof(int));
             //Set Pen
             Pen pen;
             pen.setForeR(R);
             pen.setForeG(G);
             pen.setForeB(B);
             pen.setLineWidth(lineWidth);
             pen.setPenStyle(penStyle);

             //Ellipse Brush
             in.read(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&brushstyle), sizeof(int));
             //Set Brush
             Brush brush;
             brush.setBackR(R);
             brush.setBackG(G);
             brush.setBackB(B);
             brush.setBrushStyle(brushstyle);

             //Ellipse Coordinates
             in.read(reinterpret_cast<char*>(&a), sizeof(int));
             in.read(reinterpret_cast<char*>(&b), sizeof(int));

             //New Layout
             shared_ptr<Ellipse> pEllipse;
             layouts.list.push_back(pEllipse=shared_ptr<Ellipse>(new Ellipse(PosX,
                 PosY,SHAPE::ELLIPSE,string("Ellipse"),scaleX,scaleY,angle,pen,brush,a,b)));
             Params params;
             params.setType(NOTIFY::UPDATE_IMAGE_ADD);
             params.setInts({(int)layouts.list.size()-1});
             notify(params);
             break;
         }

         case SHAPE::RECT:
         {
             //BaseShape Data
             in.read(reinterpret_cast<char*>(&PosX), sizeof(int));
             in.read(reinterpret_cast<char*>(&PosY), sizeof(int));
             in.read(reinterpret_cast<char*>(&scaleX), sizeof(double));
             in.read(reinterpret_cast<char*>(&scaleY), sizeof(double));
             in.read(reinterpret_cast<char*>(&angle), sizeof(double));

             //Rectangle Pen
             in.read(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&lineWidth), sizeof(int));
             in.read(reinterpret_cast<char*>(&penStyle), sizeof(int));
             //Set Pen
             Pen pen;
             pen.setForeR(R);
             pen.setForeG(G);
             pen.setForeB(B);
             pen.setLineWidth(lineWidth);
             pen.setPenStyle(penStyle);

             //Rectangle Brush
             in.read(reinterpret_cast<char*>(&R), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&G), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&B), sizeof(unsigned char));
             in.read(reinterpret_cast<char*>(&brushstyle), sizeof(int));
             //Set Brush
             Brush brush;
             brush.setBackR(R);
             brush.setBackG(G);
             brush.setBackB(B);
             brush.setBrushStyle(brushstyle);

             //Rectangle Coordinates
             in.read(reinterpret_cast<char*>(&width), sizeof(int));
             in.read(reinterpret_cast<char*>(&height), sizeof(int));

             //New Layout
             shared_ptr<Rect> pRect;
             layouts.list.push_back(pRect = shared_ptr<Rect>(new Rect(PosX,
                  PosY, SHAPE::RECT,string("Rectangle"),scaleX,scaleY,angle,pen,brush,width,height)));
             Params params;
             params.setType(NOTIFY::UPDATE_IMAGE_ADD);
             params.setInts({(int)layouts.list.size()-1});
             notify(params);
             break;
         }

         case SHAPE::PIXMAP:
             break;
         }
     }

     in.close();
     return;
 }

 void Model::addImage(string fileName)
 {
     shared_ptr<Pixmap> newImage(new Pixmap(string("image"),fileName));
    if(newImage->GetFormat()==PIXMAP::FMT_NULL)
    {
        Params params;
        params.setType(NOTIFY::ADD_IMAGE_FAILED);
        notify(params);
        return;
    }
    layouts.list.push_back(newImage);
    addDoneEvent(COMMAND::CREATE,layouts.list.size()-1,shared_ptr<BaseShape>(new Pixmap(*newImage)));
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_ADD);
    params.setInts({(int)layouts.list.size()-1});
    notify(params);
 }

 void Model::addDoneEvent(int commandtype,int layoutindex,shared_ptr<BaseShape> aftershape,shared_ptr<BaseShape> beforeshape){
    //delete ->before valid create ->after valid modify before after valid
     //add an event
    if(NowDoneIndex==MaxDoneIndex){
        DoneList.push_back(DoneInfo(commandtype,layoutindex,aftershape,beforeshape));
        NowDoneIndex++;
        MaxDoneIndex=NowDoneIndex;
    }else if(NowDoneIndex<MaxDoneIndex){
        NowDoneIndex++;
        MaxDoneIndex=NowDoneIndex;
        DoneList[NowDoneIndex]=DoneInfo(commandtype,layoutindex,aftershape,beforeshape);
    }else{
        //Wrong!
        qDebug()<<"DoneList Wrong!!";
    }
 }

 void Model::redo(){
    if(NowDoneIndex>=MaxDoneIndex){
        //Cannot redo
        qDebug()<<"Cannot redo";
    }else{
        NowDoneIndex++;
        //Now Assume that there is no delete in the operation.
        DoneInfo nowInfo=DoneList[NowDoneIndex];
        switch(nowInfo.getcommandtype()){
        case COMMAND::CREATE:{
            //redo create
            int insertindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+insertindex;
            layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_ADD);
            params.setInts({(int)insertindex});
            notify(params);}
            break;
        case COMMAND::DELETE:
            break;
        case COMMAND::MODIFY:
            break;
        }


    }
 }

 void Model::undo(){
    if(NowDoneIndex>=0){
        //Now Assume that the insert must be in the last layout.
        DoneInfo nowInfo=DoneList[NowDoneIndex];
        switch(nowInfo.getcommandtype()){
        case COMMAND::CREATE:{
            //Undo Create
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+nowInfo.getlayoutindex();
            layouts.list.erase(it);
            NowDoneIndex--;
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_MINUS);
            params.setInts({(int)nowInfo.getlayoutindex()});
            notify(params);}
            break;
        case COMMAND::DELETE:
            break;
        case COMMAND::MODIFY:
            break;
        }


    }else{
        qDebug()<<"Cannot undo";
    }
 }
