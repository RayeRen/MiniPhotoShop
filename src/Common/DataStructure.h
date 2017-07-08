#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <utility>
#include <string>
#include <src/Constants.h>

using namespace std;

class Pen {
protected:
    unsigned char foreR, foreG, foreB;
    int penStyle, lineWidth;
public:
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
    BaseShape(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle) : posX(posX), posY(posY), type(type), name(name), scaleX(scaleX), scaleY(scaleY), angle(angle) {}

    void setPosX(int posX) {
        BaseShape::posX = posX;
    }

    void setPosY(int posY) {
        BaseShape::posY = posY;
    }

    int getType() const {
        return type;
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
    Brush brush;
    int x1, y1, x2, y2;
public:
    Line(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle, const Pen &pen,
         const Brush &brush, int x1, int y1, int x2, int y2) : BaseShape(posX, posY, type, name, scaleX, scaleY, angle),
                                                               pen(pen), brush(brush), x1(x1), y1(y1), x2(x2), y2(y2) {}

    const Pen &getPen() const {
        return pen;
    }

    void setPen(const Pen &pen) {
        Line::pen = pen;
    }

    const Brush &getBrush() const {
        return brush;
    }

    void setBrush(const Brush &brush) {
        Line::brush = brush;
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

#endif // DATASTRUCTURE_H
