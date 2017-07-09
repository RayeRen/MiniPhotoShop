#include "../Common/DataStructure.h"
#include <cstdlib>
//#include <memory.h>

typedef unsigned char UNUM8;	//8位无符号数
typedef unsigned short UNUM16;	//16位无符号数
typedef unsigned int UNUM32;	//32位无符号数
typedef signed char SNUM8;		//8位有符号数
typedef signed short SNUM16;	//16位有符号数
typedef signed int SNUM32;

Pixmap::Pixmap(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle,unsigned int width,
               unsigned int height,unsigned char value):BaseShape(posX, posY, type, name, scaleX, scaleY, angle)
{
    r = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    g = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    b = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    a = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    memset(r, value, width*height);
    memset(g, value, width*height);
    memset(b, value, width*height);
    memset(a, value, width*height);
    format = PIXMAP::FMT_RGB;
}

Pixmap::Pixmap(int posX, int posY, int type, const string &name, double scaleX, double scaleY, double angle,string fileName)
    :r(NULL),g(NULL),b(NULL),width(0),height(0),format(PIXMAP::FMT_NULL),BaseShape(posX, posY, type, name, scaleX, scaleY, angle)
{
    QImage tmpImage(QString::fromStdString(fileName));
    tmpImage.convertToFormat(QImage::Format_ARGB32);
    if(!tmpImage.isNull())
        Load(tmpImage);
}

int Pixmap::Load(const Pixmap &pixmap)
{
    if ((format = pixmap.format) != PIXMAP::FMT_NULL)
    {
        height = pixmap.height;
        width = pixmap.width;
        r = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
        g = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
        b = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
        a = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
        memcpy(r, pixmap.r, width*height);
        memcpy(g, pixmap.g, width*height);
        memcpy(b, pixmap.b, width*height);
        memcpy(a, pixmap.a, width*height);
        return 0;
    }
    else
        FreePixmap();
    return 0;
}

void Pixmap::FreePixmap()
{
    free(r);
    free(g);
    free(b);
    free(a);
    r = NULL;
    g = NULL;
    b = NULL;
    a = NULL;
    width = 0;
    height = 0;
    format = PIXMAP::FMT_NULL;
}

int Pixmap::Load(const QImage &image)
{
    if(image.isNull())
        return 1;
    FreePixmap();
    width=image.width();
    height=image.height();
    r = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    g = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    b = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    a = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    format=PIXMAP::FMT_RGB;
    QColor color;
    unsigned char *pr=r,*pg=g,*pb=b,*pa=a;

    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
        {
            color=image.pixelColor(QPoint(x,y));
            *pr++=color.red();
            *pg++=color.green();
            *pb++=color.blue();
            *pa++=color.alpha();
        }

}

shared_ptr<QImage> Pixmap::Output()
{
    if(format==PIXMAP::FMT_NULL||height==0||width==0)
        return nullptr;
    shared_ptr<QImage> image(new QImage(QSize(width,height),QImage::Format_ARGB32));
    QColor color;
    unsigned char *pr=r,*pg=g,*pb=b,*pa=a;

    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
        {
            color.setRed(*pr++);
            color.setGreen(*pg++);
            color.setBlueF(*pb++);
            color.setAlpha(*pa++);
            image->setPixelColor(QPoint(x,y),color);
        }
    return image;
}
