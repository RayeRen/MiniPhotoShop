//
// Created by Raye on 2017/7/7.
//

#ifndef MINIPHOTOSHOP_CONSTANTS_H
#define MINIPHOTOSHOP_CONSTANTS_H

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



#endif //MINIPHOTOSHOP_CONSTANTS_H
