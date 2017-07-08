# Data Structure
## Pen
```cpp

struct Pen
{
 unsigned char foreR,foreG,foreB;
 double lineWidth;
 int penStyle;
 }
```

## Brush
 ```cpp
 struct Brush
 {
  unsigned char backR,backG,backB;
  int brushStyle;
  }
 ```
## BaseShape
```cpp
enum {SHAPE_LINE,SHAPE_ELLIPSE,SHAPE_RECT,SHAPE_PIXMAP}
 class BaseShape
 {
  int posX,posY;
  int type;
  string name;
 }
```

## Line
```cpp
class Line:public BaseShape
{
    Pen pen;
    Brush brush;
    int x1,y1,x2,y2;
}
```

## Ellipse
```cpp
class Ellipse:public BaseShape
{
    Pen pen;
    Brush brush;
    int a,b;
}
```

## Rect
```cpp
class Rect:public BaseShape
{
    Pen pen;
    Shape shape;
    int width,height;
}
```

## Polygon
```cpp
class Polygon:public BaseShape
{
    Pen pen;
    Brush brush;
    vector<int> posX,poxY;
}
```

## Pixmap
```cpp
class Pixmap:public BaseShape
{
    
}
```

## Layouts
```cpp
class Layouts
{
    vector<BaseShape*> list;
    
    BaseShape* GetLayout(int level);
    bool DeleteLayout(BaseShape*);
    bool DeleteLayout(int level);
    bool AddLayout(BaseShape*);
}
```

# Constants
```cpp=
//Shape
namespace SHAPE {
    enum {
        LINE, ELLIPSE, RECT, PIXMAP
    };
}

//Pen
namespace PEN {
    enum {
        COLOR,LINE_WEIGHT,STYLE
    };
}

namespace PENSTYLE {
    enum {
        SOLID,DASH,DOT,DASH_DOT,DASH_DOT_DOT
    };
}

//Brush
namespace BRUSH {
    enum {
        COLOR,STYLE
    };
}
```

# Commands

## AddLineCommand
- params:
    - ints
        - x1
        - y1
        - x2
        - y2

## EraseCommand
- params:
    - ints
        - x
        - y
    - doubles
        - scale
        
## AddCircleCommand
- params:
    - ints
        - x
        - y
    - doubles
        - radius

## AddRectCommand
- params
    - ints
        - x1
        - y1
        - x2
        - y2

## AddPolygonCommand
- params
    - ints
        - x1
        - y1
        - x2
        - y2

## AddTextCommand
- params
    

## AddEllipseCommand
- params
    - ints

## SetPen
- params
    - strings
        - type(color | weight)
    - ints
        - value

## LoadCommand
*.png *.jpg *.bmp *.jpeg *.pbm *.gif *.pgm *.ppm *.xbm *.xpm
- params
    - strings
        - path(e.g. ../../xxx.TYPE)

## SaveCommand
- params 
    - ints
        - type(jpg,bmp)
    - string
        - path(e.g. .../.../xx.TYPE)

# Observer
## model2vm
- params
    - ints
        - type

## vm2view


