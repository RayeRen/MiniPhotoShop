#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <utility>
#include <string>

using namespace std;

class Pen {
protected:
    unsigned char foreR, foreG, foreB;
    int penStyle = 1, lineWidth = 4;
public:
    Pen() : foreR(0), foreG(0), foreB(0),penStyle() {

    }

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
    Brush():backR(0), backG(0), backB(0),brushStyle();
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

public:
    BaseShape(int posX, int posY, int type);

    int getPosX() const;

    int getPosY() const;

    void setPos(pair<int, int> &Pos);

    string getName() const;
};

class Line : public BaseShape {
private:
    Pen pen;
    Brush brush;
    int x1, y1, x2, y2;
public:
    Line(pair<int, int> &Pos, int type, const Pen &pen, const Brush &brush, pair<int, int> &XY1, pair<int, int> &XY2);

    void setPen(Pen &pen);

    void setBrush(Brush &brush);

    void MoveTo(pair<int, int> &Pos);

};

#endif // DATASTRUCTURE_H
