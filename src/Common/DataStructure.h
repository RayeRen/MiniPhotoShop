#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include "../Constants.h"
#include <QImage>
#include <memory>
using namespace std;

class Pen {
protected:
    unsigned char foreR, foreG, foreB;
    int penStyle, lineWidth;
public:

    Pen() : foreR(255), foreG(0), foreB(0),penStyle(PENSTYLE::SOLID),lineWidth(4){

    }

    Pen(unsigned char foreR, unsigned char foreG, unsigned char foreB, int penStyle, int lineWidth) : foreR(foreR), foreG(foreG), foreB(foreB), penStyle(penStyle),lineWidth(lineWidth) {}


    unsigned char getForeR() const {
        return foreR;
    }

    void setForeR(unsigned char foreR) {
        Pen::foreR = foreR;
    }

    unsigned char getForeG() const {
        return foreG;
    }

    void setForeG(unsigned char foreG) {
        Pen::foreG = foreG;
    }

    unsigned char getForeB() const {
        return foreB;
    }

    void setForeB(unsigned char foreB) {
        Pen::foreB = foreB;
    }

    int getPenStyle() const {
        return penStyle;
    }

    void setPenStyle(int penStyle) {
        Pen::penStyle = penStyle;
    }

    int getLineWidth() const {
        return lineWidth;
    }

    void setLineWidth(int lineWidth) {
        Pen::lineWidth = lineWidth;
    }
};

class Brush {
protected:
    unsigned char backR, backG, backB;
    int brushStyle;
public:

    Brush():backR(0), backG(0), backB(0),brushStyle(BRUSHSTYLE::SOLIDPATTERN){}

    Brush(unsigned char backR, unsigned char backG, unsigned char backB, int brushStyle) : backR(backR), backG(backG),backB(backB),brushStyle(brushStyle) {}

    unsigned char getBackR() const {
        return backR;
    }

    void setBackR(unsigned char backR) {
        Brush::backR = backR;
    }

    unsigned char getBackG() const {
        return backG;
    }

    void setBackG(unsigned char backG) {
        Brush::backG = backG;
    }

    unsigned char getBackB() const {
        return backB;
    }

    void setBackB(unsigned char backB) {
        Brush::backB = backB;
    }

    int getBrushStyle() const {
        return brushStyle;
    }

    void setBrushStyle(int brushStyle) {
        Brush::brushStyle = brushStyle;
    }
};

class BaseShape {
protected:
    int posX, posY;
    int type;
    string name;
    double scaleX, scaleY, angle;
public:
    BaseShape(double posX, double posY, int type, const string &name, double scaleX, double scaleY, double angle) : posX(posX), posY(posY), type(type), name(name), scaleX(scaleX), scaleY(scaleY), angle(angle) {}

    void setPosX(int posX) {
        BaseShape::posX = posX;
    }

    void setPosY(int posY) {
        BaseShape::posY = posY;
    }

    int getType() const {
        return type;
    }

    int getPosX() const {
        return posX;
    }


    int getPosY() const {
        return posY;
    }

    void setType(int type) {
        BaseShape::type = type;
    }

    void setName(const string &name) {
        BaseShape::name = name;
    }

    string getName()const
    {
        return name;
    }

    double getScaleX() const {
        return scaleX;
    }

    void setScaleX(double scaleX) {
        BaseShape::scaleX = scaleX;
    }

    double getScaleY() const {
        return scaleY;
    }

    void setScaleY(double scaleY) {
        BaseShape::scaleY = scaleY;
    }

    double getAngle() const {
        return angle;
    }

    void setAngle(double angle) {
        BaseShape::angle = angle;
    }
};

class Line : public BaseShape {
protected:
    Pen pen;
    int x1, y1, x2, y2;
public:
    Line(int posX,int posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,
         int x1, int y1, int x2, int y2) : BaseShape(posX, posY, type, name, scaleX, scaleY, angle),
        pen(pen),  x1(x1), y1(y1), x2(x2), y2(y2) {}

    const Pen &getPen() const {
        return pen;
    }

    void setPen(const Pen &pen) {
        Line::pen = pen;
    }

    int getX1() const {
        return x1;
    }

    void setX1(int x1) {
        Line::x1 = x1;
    }

    int getY1() const {
        return y1;
    }

    void setY1(int y1) {
        Line::y1 = y1;
    }

    int getX2() const {
        return x2;
    }

    void setX2(int x2) {
        Line::x2 = x2;
    }

    int getY2() const {
        return y2;
    }

    void setY2(int y2) {
        Line::y2 = y2;
    }

};
class Ellipse:public BaseShape
{
protected:
    Pen pen;
    Brush brush;
    int a,b;
public:
    Ellipse(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,const Brush &brush,
            int a, int b) : BaseShape(posX, posY, type, name, scaleX, scaleY, angle),
        pen(pen),brush(brush),  a(a), b(b){}
    void setBrushColor(unsigned char r,unsigned char g,unsigned char b)
    {
        brush.setBackR(r);
        brush.setBackG(g);
        brush.setBackB(b);
    }

    void setBrushStyle(int newStyle)
    {
        brush.setBrushStyle(newStyle);
    }

    const Pen &getPen() const {
        return pen;
    }

    void setPen(const Pen &pen) {
        Ellipse::pen = pen;
    }
    const Brush &getBrush()const{
        return brush;
    }
    void setBrush(const Brush &brush){
        Ellipse::brush=brush;
    }

    int getA() const {
        return a;
    }

    void setA(int a) {
        Ellipse::a = a;
    }

    int getB() const {
        return b;
    }

    void setB(int b) {
        Ellipse::b = b;
    }

};

class Rect:public BaseShape
{
protected:
    Pen pen;
    Brush brush;
    int width, height;

public:
    Rect(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,const Brush &brush,
         int width, int height):BaseShape(posX, posY, type, name, scaleX, scaleY, angle),
        pen(pen),brush(brush), width(width), height(height){}

    const Pen &getPen() const {
        return pen;

    }
    void setBrushColor(unsigned char r,unsigned char g,unsigned char b)
    {
        brush.setBackR(r);
        brush.setBackG(g);
        brush.setBackB(b);
    }

    void setBrushStyle(int newStyle)
    {
        brush.setBrushStyle(newStyle);
    }

    const Brush &getBrush()const{
        return brush;
    }

    void setPen(const Pen &pen) {
        Rect::pen = pen;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width){
        Rect::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height){
        Rect::height = height;
    }
};

class Pixmap:public BaseShape
{
    unsigned int height, width, format;	//height为图像高度 width为图像宽度 format为状态
    unsigned char  *r, *g, *b, *a;	//r、g、b、a为4个通道的数组 顺序为从左下到右上，先行后列
public:
    Pixmap(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle,unsigned int width, unsigned int height,unsigned char value=0);
    Pixmap(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle,string fileName);
    Pixmap(const Pixmap &pixmap) :BaseShape(pixmap),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(PIXMAP::FMT_NULL) { Load(pixmap); }
    ~Pixmap() { FreePixmap(); }
    int Load(const Pixmap &pixmap);
    int Load(const QImage &image);
    void FreePixmap();	//清空数据
    shared_ptr<QImage> Output();
    unsigned int GetFormat(){return format;}
    unsigned int GetWidth(){return width;}
    unsigned int GetHeight(){return height;}

    const unsigned char *getR(unsigned int x, unsigned int y) const { if (x < width&&y < height) return r + y*width + x; return NULL; }//返回(x,y)坐标处的r值指针
    const unsigned char *getG(unsigned int x, unsigned int y) const { if (x < width&&y < height)return g + y*width + x; return NULL; } //返回(x,y)坐标处的g值指针
    const unsigned char *getB(unsigned int x, unsigned int y) const { if (x < width&&y < height) return b + y*width + x; return NULL; } //返回(x,y)坐标处的b值指针
    const unsigned char *getA(unsigned int x, unsigned int y) const { if (x < width&&y < height) return a + y*width + x; return NULL; } //返回(x,y)坐标处的a值指针
};

#endif // DATASTRUCTURE_H
