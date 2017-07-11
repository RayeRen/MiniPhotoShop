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
    void LayoutTransform(int Change,int LayoutIndex);
    void LayoutOrderChange(int beforeLayoutIndex,int afterLayoutIndex,int mode=0){
        if(beforeLayoutIndex<0||beforeLayoutIndex>=layouts.list.size())return;
        if(afterLayoutIndex<0||afterLayoutIndex>=layouts.list.size())return;
        if(beforeLayoutIndex==afterLayoutIndex)return;
        int realafter=afterLayoutIndex;
        if(afterLayoutIndex>beforeLayoutIndex){
            realafter++;
        }
        vector<shared_ptr<BaseShape>>::iterator beforeit=layouts.list.begin()+beforeLayoutIndex;
        vector<shared_ptr<BaseShape>>::iterator afterit=layouts.list.begin()+realafter;
        layouts.list.insert(afterit,*beforeit);
        Params params;
        params.setType(NOTIFY::UPDATE_IMAGE_ADD);
        params.setInts({(int)realafter});
        notify(params);

        int notifyindex=beforeLayoutIndex;
        if(notifyindex>=afterLayoutIndex){
            notifyindex++;
        }
        beforeit=layouts.list.begin()+notifyindex;
        layouts.list.erase(beforeit);

        Params newparams;
        newparams.setType(NOTIFY::UPDATE_IMAGE_MINUS);
        newparams.setInts({(int)notifyindex});
        notify(newparams);
        if(!mode)addDoneEvent(COMMAND::ORDERCHANGE,afterLayoutIndex,nullptr,nullptr,beforeLayoutIndex);

    }

    void DeleteLayout(int LayoutIndex);
    void PixmapFilter(Params params);
    void clearDoneEvent();

    void addDoneEvent(int commandtype,int layoutindex,shared_ptr<BaseShape> aftershape=nullptr,shared_ptr<BaseShape> beforeshape=nullptr,int beforelayoutindex=-1);
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
