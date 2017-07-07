#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <utility>
#include <string>
using namespace std;

struct Pen
{
    unsigned char foreR, foreE, foreB;
    double lineWidth;
    int penStyle;
};

struct Brush
{
    unsigned char backR, backG, backB;
    int brushStyle;
};

class BaseShape
{
protected:
    int posX, posY;
    int type;
    string name;

public:
    BaseShape(int posX, int posY, int type);
    pair<int, int> getPos()const;
    void setPos(pair<int, int>& Pos);
    string getName()const;
};

class Line:public BaseShape
{
private:
    Pen pen;
    Brush brush;
    int x1, y1, x2, y2;
public:
    Line(pair<int, int>& Pos, int type, const Pen &pen, const Brush &brush, pair<int, int>& XY1, pair<int, int>& XY2);
    void setPen(Pen &pen);
    void setBrush(Brush& brush);
    void MoveTo(pair<int, int>& Pos);

};

#endif // DATASTRUCTURE_H
