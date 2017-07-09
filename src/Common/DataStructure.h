#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include "../Constants.h"

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

    Brush():backR(0), backG(0), backB(0),brushStyle(){}

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
    double posX, posY;
    int type;
    string name;
    double scaleX, scaleY, angle;
public:
    BaseShape(double posX, double posY, int type, const string &name, double scaleX, double scaleY, double angle) : posX(posX), posY(posY), type(type), name(name), scaleX(scaleX), scaleY(scaleY), angle(angle) {}

    void setPosX(double posX) {
        BaseShape::posX = posX;
    }

    void setPosY(double posY) {
        BaseShape::posY = posY;
    }

    int getType() const {
        return type;
    }

    double getPosX() const {
        return posX;
    }


    double getPosY() const {
        return posY;
    }

    void setType(int type) {
        BaseShape::type = type;
    }

    void setName(const string &name) {
        BaseShape::name = name;
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
    double x1, y1, x2, y2;
public:
    Line(double posX, double posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,
          double x1, double y1, double x2, double y2) : BaseShape(posX, posY, type, name, scaleX, scaleY, angle),
                                                               pen(pen),  x1(x1), y1(y1), x2(x2), y2(y2) {}

    const Pen &getPen() const {
        return pen;
    }

    void setPen(const Pen &pen) {
        Line::pen = pen;
    }

    double getX1() const {
        return x1;
    }

    void setX1(double x1) {
        Line::x1 = x1;
    }

    double getY1() const {
        return y1;
    }

    void setY1(double y1) {
        Line::y1 = y1;
    }

    double getX2() const {
        return x2;
    }

    void setX2(double x2) {
        Line::x2 = x2;
    }

    double getY2() const {
        return y2;
    }

    void setY2(double y2) {
        Line::y2 = y2;
    }

};
class Ellipse:public BaseShape
{
protected:
    Pen pen;
    Brush brush;
    double a,b;
public:
    Ellipse(double posX, double posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,
          double a, double b) : BaseShape(posX, posY, type, name, scaleX, scaleY, angle), Brush(),
                                                               pen(pen),  a(a), b(b){}
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

    const Pen &getPen() const {
        return pen;
    }

    void setPen(const Pen &pen) {
        Ellipse::pen = pen;
    }

    double getA() const {
        return a;
    }

    void setA(double a) {
        Ellipse::a = a;
    }

    double getB() const {
        return b;
    }

    void setB(double b) {
        Ellipse::b = b;
    }

};

class Rect:public BaseShape
{
protected:
    Pen pen;
    Brush brush;
    double width, height;

public:
    Rect(double posX, double posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,
         double width, double height):BaseShape(posX, posY, type, name, scaleX, scaleY, angle), Brush(),
                    pen(pen), width(width), height(height){}

    const Pen &getPen() const {
        return pen;

    }void setBrushColor(unsigned char r,unsigned char g,unsigned char b)
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

    double getWidth() const {
        return width;
    }

    void setWidth(double width){
        Rect::width = width;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double height){
        Rect::height = height;
    }
};

#endif // DATASTRUCTURE_H
