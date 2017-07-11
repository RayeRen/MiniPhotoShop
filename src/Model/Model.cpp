//
// Created by Raye on 2017/7/6.
//

#include "Model.h"
#include <QDebug>
#include <iostream>
#include <fstream>
Model::Model(){
    ClearModel();
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
void Model::addBaseShape(vector<shared_ptr<BaseShape>>::iterator  it,shared_ptr<BaseShape> shape){
    //Redo Need it.
    if(shape!=nullptr){
        layouts.list.insert(it,NewBaseShape(shape));
    }
}
shared_ptr<BaseShape> Model::NewBaseShape(shared_ptr<BaseShape> shape){
    shared_ptr<BaseShape> newBaseShape=nullptr;
    if(shape!=nullptr){
        int type=shape->getType();
        if(type==SHAPE::LINE){
            newBaseShape=shared_ptr<BaseShape>(new Line(*(static_pointer_cast<Line>(shape))));
        }else if(type==SHAPE::ELLIPSE){
            newBaseShape=shared_ptr<BaseShape>(new Ellipse(*(static_pointer_cast<Ellipse>(shape))));
        }else if(type==SHAPE::RECT){
            newBaseShape=shared_ptr<BaseShape>(new Rect(*(static_pointer_cast<Rect>(shape))));
        }else if(type==SHAPE::PIXMAP){
            newBaseShape=shared_ptr<BaseShape>(new Pixmap(*(static_pointer_cast<Pixmap>(shape))));
        }else{
        }
    }else{
        qDebug()<<"The shape is null";
    }
    return newBaseShape;
}
void Model::LayoutChange(int Change,int LayoutIndex){
    if(Change==1){
        //Begin
        ChangeBegin=Change;
        ChangeLayout=LayoutIndex;
        qDebug()<<"Save";
        tempShape=NewBaseShape(layouts.list.at(LayoutIndex));
    }else if(ChangeBegin==1){
        //End
        ChangeBegin=0;
        qDebug()<<"End";
        if(ChangeLayout==LayoutIndex){
            qDebug()<<"Save Done";
            addDoneEvent(COMMAND::MODIFY,LayoutIndex,NewBaseShape(layouts.list.at(LayoutIndex)),tempShape);
            tempShape=nullptr;
        }
    }
}
void Model::DeleteLayout(int LayoutIndex){
    if(LayoutIndex<0)return;
    vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+LayoutIndex;
    addDoneEvent(COMMAND::DELETE,LayoutIndex,nullptr,NewBaseShape(layouts.list.at(LayoutIndex)));

    layouts.list.erase(it);
    qDebug()<<"Model Delete is Over .Next Delete";
    Params params;
    params.setType(NOTIFY::UPDATE_IMAGE_MINUS);
    params.setInts({(int)LayoutIndex});
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
     clearDoneEvent();
 }

 bool Model::isProjectEmpty()const
 {
     return layouts.list.empty();
 }

 void Model::newProject()
 {
     qDebug()<<"newProject";
     ClearModel();
     Params params;
     params.setType(NOTIFY::CLEAR);
     notify(params);
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
         {
             shared_ptr<Pixmap> pixmap;
             pixmap = shared_ptr<Pixmap>(static_pointer_cast<Pixmap>(layouts.list[i]));
             //BaseShape Data
             int PosX, PosY;
             double ScaleX, ScaleY, Angle;
             PosX = pixmap->getPosX();
             PosY = pixmap->getPosY();
             ScaleX = pixmap->getScaleX();
             ScaleY = pixmap->getScaleY();
             Angle = pixmap->getAngle();
             out.write(reinterpret_cast<char*>(&PosX), sizeof(int));
             out.write(reinterpret_cast<char*>(&PosY), sizeof(int));
             out.write(reinterpret_cast<char*>(&ScaleX), sizeof(double));
             out.write(reinterpret_cast<char*>(&ScaleY), sizeof(double));
             out.write(reinterpret_cast<char*>(&Angle), sizeof(double));

             //Pixmap Data
             int width, height, format;
             width = pixmap->GetWidth();
             height = pixmap->GetHeight();
             format = pixmap->GetFormat();
             out.write(reinterpret_cast<char*>(&width), sizeof(int));
             out.write(reinterpret_cast<char*>(&height), sizeof(int));
             out.write(reinterpret_cast<char*>(&format), sizeof(int));

             UNUM8 *r, *g, *b, *a;
             r = pixmap->getRHead();
             g = pixmap->getGHead();
             b = pixmap->getBHead();
             a = pixmap->getAHead();
             out.write(reinterpret_cast<char*>(r), width * height);
             out.write(reinterpret_cast<char*>(g), width * height);
             out.write(reinterpret_cast<char*>(b), width * height);
             out.write(reinterpret_cast<char*>(a), width * height);
             break;
         }
         }
     }

     out.close();
 }

 void Model::loadProject(string path)
 {
     fstream in;
     int type;
     char head[30];
     int PosX, PosY, x1, y1, x2, y2, a, b, width, height, penStyle, lineWidth, brushstyle, format;
     unsigned char R, G, B;
     double scaleX, scaleY, angle;

     ClearModel();
     Params params;
     params.setType(NOTIFY::CLEAR);
     notify(params);

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
         {
             //BaseShape Data
             in.read(reinterpret_cast<char*>(&PosX), sizeof(int));
             in.read(reinterpret_cast<char*>(&PosY), sizeof(int));
             in.read(reinterpret_cast<char*>(&scaleX), sizeof(double));
             in.read(reinterpret_cast<char*>(&scaleY), sizeof(double));
             in.read(reinterpret_cast<char*>(&angle), sizeof(double));

             //Pixmap Data
             in.read(reinterpret_cast<char*>(&width), sizeof(int));
             in.read(reinterpret_cast<char*>(&height), sizeof(int));
             in.read(reinterpret_cast<char*>(&format), sizeof(int));

             UNUM8 *r, *g, *b, *a;
             r = (UNUM8 *)malloc(width * height);
             g = (UNUM8 *)malloc(width * height);
             b = (UNUM8 *)malloc(width * height);
             a = (UNUM8 *)malloc(width * height);
             in.read(reinterpret_cast<char*>(r), width * height);
             in.read(reinterpret_cast<char*>(g), width * height);
             in.read(reinterpret_cast<char*>(b), width * height);
             in.read(reinterpret_cast<char*>(a), width * height);

             //New Pixmap
             shared_ptr<Pixmap> ppixmap;
             layouts.list.push_back(ppixmap = shared_ptr<Pixmap>(new Pixmap(width, height)));
             memcpy(ppixmap->getRHead(), r, width * height);
             memcpy(ppixmap->getGHead(), g, width * height);
             memcpy(ppixmap->getBHead(), b, width * height);
             memcpy(ppixmap->getAHead(), a, width * height);
             ppixmap->setPosX(PosX);
             ppixmap->setPosY(PosY);
             ppixmap->setScaleX(scaleX);
             ppixmap->setScaleY(scaleY);
             ppixmap->setAngle(angle);

             Params params;
             params.setType(NOTIFY::UPDATE_IMAGE_ADD);
             params.setInts({(int)layouts.list.size()-1});
             notify(params);
             free(r);
             free(g);
             free(b);
             free(a);
             break;
         }
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
 void Model::PixmapFilter(Params params){
     //ints的第0个是layoutindex.
     int type=params.getType();
     vector<int> ints=params.getInts();
     vector<double> doubles=params.getDoubles();
     int layoutindex=ints[0];
     if(layoutindex<0)return;
     if(layouts.list.at(layoutindex)->getType()!=SHAPE::PIXMAP)return;
     shared_ptr<Pixmap> pic(static_pointer_cast<Pixmap>(layouts.list.at(layoutindex)));
     shared_ptr<BaseShape> tempPic(NewBaseShape(layouts.list.at(layoutindex)));
     if(pic==nullptr)return;
     switch(type){
     case PIXMAP::LAPLACIANENHANCE:{
         int size;
         size=ints[0];
         double* conv=NULL;
         if(size>0){
            conv=new double[size*size];
            double *nowconv=conv;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    *(nowconv++)=doubles[i*size+j];
                }
            }
         }else{

         }
         pic->LaplacianEnhance(conv,size);
     }
         break;
     case PIXMAP::BILATERALFILTERING:
         pic->BilateralFiltering(ints[1],doubles[0],doubles[1]);
         break;
     case PIXMAP::HISTOEQUALIZING:
         pic->HistoEqualizing();
         break;
     case PIXMAP::INVERSECOLOR:
         pic->InverseColor();
         break;
     case PIXMAP::LOGOPERATION:
         pic->LogOperation();
         break;
     default:
         return;
         break;
     }
     addDoneEvent(COMMAND::MODIFY,layoutindex,NewBaseShape(layouts.list.at(layoutindex)),tempPic);
     Params newparams;
     newparams.setType(NOTIFY::UPDATE_IMAGE);
     newparams.setInts({(int)layoutindex});
     notify(newparams);

 }
 void Model::clearDoneEvent(){
     NowDoneIndex=-1;
     MaxDoneIndex=-1;
     ChangeBegin=0;
     ChangeLayout=-1;
     tempShape=nullptr;
     DoneList.clear();
 }
 void Model::addDoneEvent(int commandtype,int layoutindex,shared_ptr<BaseShape> aftershape,shared_ptr<BaseShape> beforeshape){
    //delete ->before valid create ->after valid modify before after valid
     //add an event
     qDebug()<<"Begin Add Done Event";
    if(NowDoneIndex==MaxDoneIndex){
        DoneList.push_back(DoneInfo(commandtype,layoutindex,aftershape,beforeshape));
        NowDoneIndex++;
        MaxDoneIndex=NowDoneIndex;
    }else if(NowDoneIndex<MaxDoneIndex){
        qDebug()<<"Now Index"<<NowDoneIndex<<"Max Index"<<MaxDoneIndex<<"DoneList Count"<<DoneList.size();
        vector<DoneInfo>::iterator it;
        int offset=NowDoneIndex+1;
        for(it=DoneList.begin()+offset;it!=DoneList.end();){
            qDebug()<<"Where";
            it=DoneList.erase(it);
        }
        DoneList.push_back(DoneInfo(commandtype,layoutindex,aftershape,beforeshape));
        NowDoneIndex++;
        MaxDoneIndex=NowDoneIndex;
    }else{
        //Wrong!
        qDebug()<<"DoneList Wrong!!";
    }
    qDebug()<<"End Push DoneList";
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
        case COMMAND::CREATE:
        {
            //redo create
            int insertindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+insertindex;
            addBaseShape(it,nowInfo.getaftershape());
            //layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_ADD);
            params.setInts({(int)insertindex});
            notify(params);
        }
            break;
        case COMMAND::DELETE:{
            //redo create
            int delindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+delindex;
            layouts.list.erase(it);
            //layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_MINUS);
            params.setInts({(int)delindex});
            notify(params);
        }
            break;
        case COMMAND::MODIFY:{
            //redo modify
            int modifyindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+modifyindex;
            *it=NewBaseShape(nowInfo.getaftershape());
            //layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE);
            params.setInts({(int)modifyindex});
            notify(params);
        }
            break;
        }


    }
 }

 void Model::undo(){
    if(NowDoneIndex>=0){
        //Now Assume that the insert must be in the last layout.
        DoneInfo nowInfo=DoneList[NowDoneIndex];
        NowDoneIndex--;
        switch(nowInfo.getcommandtype()){
        case COMMAND::CREATE:{
            //Undo Create
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+nowInfo.getlayoutindex();
            layouts.list.erase(it);

            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_MINUS);
            params.setInts({(int)nowInfo.getlayoutindex()});
            notify(params);
        }
            break;
        case COMMAND::DELETE:{
            //undo delete
            int delindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+delindex;
            addBaseShape(it,nowInfo.getbeforeshape());
            //layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE_ADD);
            params.setInts({(int)delindex});
            notify(params);
        }
            break;
        case COMMAND::MODIFY:{
            //undo modify
            int modifyindex=nowInfo.getlayoutindex();
            vector<shared_ptr<BaseShape>>::iterator it=layouts.list.begin()+modifyindex;
            *it=NewBaseShape(nowInfo.getbeforeshape());
            //layouts.list.insert(it,nowInfo.getaftershape());
            //layouts.list.push_back(DoneList[NowDoneIndex].getshape());
            Params params;
            params.setType(NOTIFY::UPDATE_IMAGE);
            params.setInts({(int)modifyindex});
            notify(params);
        }
            break;
        }


    }else{
        qDebug()<<"Cannot undo";
    }
 }
