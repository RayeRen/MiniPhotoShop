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

    int ChangeBegin,ChangeLayout;
    shared_ptr<BaseShape> tempShape;
    int NowDoneIndex,MaxDoneIndex;
    vector<DoneInfo> DoneList;
    void ClearModel();
public:
    Model();
    void addLine(){}
    void addLine(double centerX,double centerY,double x1,double y1,double x2,double y2);
    void addImage(string fileName);
    void addEllipse(double centerX,double centerY,double a,double b);//a -- x axis, b -- y axis
    void addRect(double centerX, double centerY, double width, double height);
    void LayoutChange(int Change,int LayoutIndex);
    void DeleteLayout(int LayoutIndex);
    void PixmapFilter(Params params){
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

    void addDoneEvent(int commandtype,int layoutindex,shared_ptr<BaseShape> aftershape=nullptr,shared_ptr<BaseShape> beforeshape=nullptr);
    void addBaseShape(vector<shared_ptr<BaseShape>>::iterator it,shared_ptr<BaseShape> shape);
    shared_ptr<BaseShape> NewBaseShape(shared_ptr<BaseShape> shape);

    void redo();
    void undo();
    void newProject();
    void saveProject(string path)const;
    void loadProject(string path);
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
