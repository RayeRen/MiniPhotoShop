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

namespace PENSTYLE {
    enum {
        SOLID=1,DASH,DOT,DASH_DOT,DASH_DOT_DOT
    };
}

//Notify Type
namespace NOTIFY{
enum{

    UPDATE_IMAGE,UPDATE_IMAGE_ADD,UPDATE_IMAGE_MINUS
};
}

//Command Type
namespace COMMAND {
    enum{
        UPDATE_PEN_COLOR,UPDATE_PEN_WIDTH,UPDATE_PEN_STYLE,UPDATE_BRUSH_COLOR,UPDATE_BRUSH_STYLE
    };
}

//UI states
namespace STATE{
enum{
    INIT,DRAW_LINE_INIT,DRAW_LINE,DRAW_ELLIPSE_INIT,DRAW_ELLIPSE
};
}

#endif //MINIPHOTOSHOP_CONSTANTS_H
