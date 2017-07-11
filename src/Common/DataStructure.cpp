#include "../Common/DataStructure.h"
#include <cstdlib>
#include <QDebug>
//#include <memory.h>
using namespace PIXMAP;
#ifndef PI
#define PI 3.141592
#endif
/*
typedef unsigned char UNUM8;	//8位无符号数
typedef unsigned short UNUM16;	//16位无符号数
typedef unsigned int UNUM32;	//32位无符号数
typedef signed char SNUM8;		//8位有符号数
typedef signed short SNUM16;	//16位有符号数
typedef signed int SNUM32;
*/
typedef struct strBmpFileHeader
{
    UNUM16 bfType, bfReserved1, bfReserved2;
    UNUM32 bfSize, bfOffBits;
}BmpFileHeader;

typedef struct strBmpFileInformation
{
    UNUM16 biPlanes, biBitCount;
    UNUM32 biSize, biWidth, biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant;
    SNUM32 biHeight;
}BmpFileInformation;


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

Pixmap::Pixmap(const string &name,string fileName)
    :r(NULL),g(NULL),b(NULL),a(NULL),width(0),height(0),format(PIXMAP::FMT_NULL),
      BaseShape(0, 0, SHAPE::PIXMAP, name, 1.0,1.0,0.0)
{
    QImage tmpImage(QString::fromStdString(fileName));
    tmpImage.convertToFormat(QImage::Format_ARGB32);
    if(!tmpImage.isNull())
    {
        Load(tmpImage);
       BaseShape::setPosX(width/2);
        BaseShape::setPosY(height/2);
    }

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
    QRgb color;
    unsigned char *pr=r,*pg=g,*pb=b,*pa=a;


        for(int y=0;y<height;y++)
            for(int x=0;x<width;x++)
        {
            color=image.pixel(QPoint(x,y));
            *pr++=(color>>16)&0x000000FF;
            *pg++=(color>>8)&0x000000FF;
            *pb++=color&0x000000FF;
            *pa++=(color>>24)&0x000000FF;
        }
}

shared_ptr<QImage> Pixmap::Output()
{
    if(format==PIXMAP::FMT_NULL||height==0||width==0)
        return nullptr;
    shared_ptr<QImage> image(new QImage(QSize(width,height),QImage::Format_ARGB32));
    QColor color;
    unsigned char *pr=r,*pg=g,*pb=b,*pa=a;


        for(int y=0;y<height;y++)
            for(int x=0;x<width;x++)
        {
            color.setRed(*pr++);
            color.setGreen(*pg++);
            color.setBlue(*pb++);
            color.setAlpha(*pa++);
            image->setPixel(QPoint(x,y),color.rgba());
        }
    return image;
}

//-----------------------Origin Pixmap---------------------//

int  Pixmap::LoadBmpFile(const char * fileName)
{
    BmpFileHeader fileHeader;	//文件头
    BmpFileInformation fileInfo;	//信息段
    UNUM8* palette = NULL;	//调色板
    FreePixmap();
    a = b = g = r = NULL;
    height = width = 0;
    FILE* fp;
    if (fileName == NULL)
        return 1;
    if ((fp = fopen(fileName, "rb")) == NULL)
        return 1;	//错误：无法打开文件
    fread(&fileHeader.bfType, 2, 1, fp);
    if (fileHeader.bfType != 0x4d42)
    {
        fclose(fp);
        return 1;	//错误：不是标准BMP文件
    }
    //读取文件头
    fread(&fileHeader.bfSize, 4, 1, fp);
    fread(&fileHeader.bfReserved1, 2, 1, fp);
    fread(&fileHeader.bfReserved2, 2, 1, fp);
    fread(&fileHeader.bfOffBits, 4, 1, fp);
    //读取信息段v
    fread(&fileInfo.biSize, 4, 1, fp);
    fread(&fileInfo.biWidth, 4, 1, fp);
    fread(&fileInfo.biHeight, 4, 1, fp);
    fread(&fileInfo.biPlanes, 2, 1, fp);
    fread(&fileInfo.biBitCount, 2, 1, fp);
    fread(&fileInfo.biCompression, 4, 1, fp);
    fread(&fileInfo.biSizeImage, 4, 1, fp);
    fread(&fileInfo.biXPelsPerMeter, 4, 1, fp);
    fread(&fileInfo.biYPelsPerMeter, 4, 1, fp);
    fread(&fileInfo.biClrUsed, 4, 1, fp);
    fread(&fileInfo.biClrImportant, 4, 1, fp);
    if (fileInfo.biCompression != 0)
    {
        fclose(fp);
        return -1;	//错误：非BI_RGB格式
    }

    int rowN, tmp, paletteN = 0;	//tmp为每行有效字节数 rowN为每行实际字节数
    switch (fileInfo.biBitCount)
    {
    case 1:
        paletteN = 2;
        tmp = (int)(fileInfo.biWidth / 8) + ((fileInfo.biWidth % 8) ? 1 : 0);
        rowN = tmp + ((tmp % 4) ? (4 - tmp % 4) : 0);
        break;
    case 4:
        paletteN = 16;
        tmp = (int)(fileInfo.biWidth / 2) + ((fileInfo.biWidth % 2) ? 1 : 0);
        rowN = tmp + ((tmp % 4) ? (4 - tmp % 4) : 0);
        break;
    case 8:
        paletteN = 256;
        tmp = fileInfo.biWidth;
        rowN = tmp + ((tmp % 4) ? (4 - tmp % 4) : 0);
        break;
    case 16:
        tmp = fileInfo.biWidth * 2;
        rowN = tmp + ((tmp % 4) ? (4 - tmp % 4) : 0);
        break;
    case 24:
        tmp = fileInfo.biWidth * 3;
        rowN = tmp + ((tmp % 4) ? (4 - tmp % 4) : 0);
        break;
    case 32:
        rowN = tmp = fileInfo.biWidth * 4;
        break;
    default:
        fclose(fp);
        return 1;	//错误：颜色比特数值非法
    }

    fseek(fp, 14L + fileInfo.biSize, SEEK_SET);
    //读取调色板
    if (paletteN != 0)
    {
        palette = (UNUM8*)malloc(sizeof(UNUM8)*paletteN * 4);
        fread(palette, sizeof(UNUM8) * 4, paletteN, fp);
    }

    //初始化pixmap
    width = fileInfo.biWidth;
    height = abs(fileInfo.biHeight);
    r = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    g = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    b = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    a = (UNUM8*)malloc(sizeof(UNUM8)*width*height);
    format = FMT_RGB;
    UNUM8 *colorRp = r, *colorGp = g, *colorBp = b, *colorAp = a;

    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    unsigned int x;
    int offset;//offset为当前读取字节的偏移量

    if (paletteN != 0)
    {
        //若有调色板
        for (unsigned int y = 0; y < height; y++)
        {
            UNUM8 tmpData, data;
            x = 0;
            for (int readN = 0; readN < rowN; readN++)
            {
                fread(&tmpData, 1, 1, fp);
                switch (fileInfo.biBitCount)
                {
                case 1:offset = 7; break;
                case 4:offset = 4; break;
                case 8:offset = 0; break;
                }
                while (x < fileInfo.biWidth&&offset >= 0)
                {
                    //获取颜色索引号
                    data = tmpData >> offset;
                    if (fileInfo.biBitCount == 1)
                        data &= 0x1;
                    else
                    {
                        if (fileInfo.biBitCount == 4)
                            data &= 0xF;
                    }
                    offset -= fileInfo.biBitCount;
                    x++;
                    //设置颜色
                    *colorBp++ = *(palette + data * 4);
                    *colorGp++ = *(palette + data * 4 + 1);
                    *colorRp++ = *(palette + data * 4 + 2);
                    *colorAp++ = *(palette + data * 4 + 3);
                }
            }
        }
    }
    else
    {
        //若无调色板
        int bufN = (tmp % 4) ? (4 - tmp % 4) : 0;
        UNUM32 buf;
        UNUM16 color16;
        switch (fileInfo.biBitCount)
        {
        case 16:
            //16位色处理
            for (unsigned int y = 0; y < height; y++, fread(&buf, bufN, 1, fp))
                for (unsigned int x = 0; x < width; x++)
                {
                    fread(&color16, 2, 1, fp);
                    *colorBp++ = (UNUM8)(color16 & 0x1F);
                    *colorGp++ = (UNUM8)((color16 & 0x3E0) >> 5);
                    *colorRp++ = (UNUM8)(color16 >> 10);
                    *colorAp++ = 0;
                }
            break;
        case 24:
            //24位色处理
            for (unsigned int y = 0; y < height; y++, fread(&buf, bufN, 1, fp))
                for (unsigned int x = 0; x < width; x++)
                {
                    fread(colorBp++, 1, 1, fp);
                    fread(colorGp++, 1, 1, fp);
                    fread(colorRp++, 1, 1, fp);
                    *colorAp++ = 0;
                }
            break;
        case 32:
            //32位色处理
            for (unsigned int y = 0; y < height; y++, fread(&buf, bufN, 1, fp))
                for (unsigned int x = 0; x < width; x++)
                {
                    fread(colorBp++, 1, 1, fp);
                    fread(colorGp++, 1, 1, fp);
                    fread(colorRp++, 1, 1, fp);
                    fread(colorAp++, 1, 1, fp);
                }
            break;
        }

    }
    fclose(fp);
    free(palette);
    return 0;
}

int Pixmap::SaveAsBMP24b(const char * fileName) const
{
    if (r == NULL || g == NULL || b == NULL || a == NULL || width == 0 || height == 0 || format == FMT_NULL)
        return 1;
    Pixmap tmpPic;

    if (format == FMT_YUV)
    {
        tmpPic.Load(*this);
        tmpPic.ConvertToRGB();
    }

    FILE* fp = fopen(fileName, "wb");
    if (fp == NULL)
        return 1;
    BmpFileHeader fileHeader;
    BmpFileInformation fileInfo;
    int bufN = (width * 3 % 4) ? 4 - width * 3 % 4 : 0;
    fileHeader.bfType = 0x4d42;
    fileHeader.bfSize = 54 + height*(width + bufN) * 3;
    fileHeader.bfReserved1 = fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = 54;
    fileInfo.biSize = 40;
    fileInfo.biHeight = height;
    fileInfo.biWidth = width;
    fileInfo.biPlanes = 1;
    fileInfo.biBitCount = 24;
    fileInfo.biCompression = 0;
    fileInfo.biSizeImage = 0;
    fileInfo.biXPelsPerMeter = 0;
    fileInfo.biYPelsPerMeter = 0;
    fileInfo.biClrUsed = 0;
    fileInfo.biClrImportant = 0;

    fwrite(&fileHeader.bfType, 2, 1, fp);
    fwrite(&fileHeader.bfSize, 4, 1, fp);
    fwrite(&fileHeader.bfReserved1, 2, 1, fp);
    fwrite(&fileHeader.bfReserved2, 2, 1, fp);
    fwrite(&fileHeader.bfOffBits, 4, 1, fp);

    fwrite(&fileInfo.biSize, 4, 1, fp);
    fwrite(&fileInfo.biWidth, 4, 1, fp);
    fwrite(&fileInfo.biHeight, 4, 1, fp);
    fwrite(&fileInfo.biPlanes, 2, 1, fp);
    fwrite(&fileInfo.biBitCount, 2, 1, fp);
    fwrite(&fileInfo.biCompression, 4, 1, fp);
    fwrite(&fileInfo.biSizeImage, 4, 1, fp);
    fwrite(&fileInfo.biXPelsPerMeter, 4, 1, fp);
    fwrite(&fileInfo.biYPelsPerMeter, 4, 1, fp);
    fwrite(&fileInfo.biClrUsed, 4, 1, fp);
    fwrite(&fileInfo.biClrImportant, 4, 1, fp);
    UNUM8  tmp[4] = { 0 };
    const UNUM8 *colorRp = r, *colorGp = g, *colorBp = b;
    if (tmpPic.format == FMT_RGB)
    {
        colorRp = tmpPic.r;
        colorGp = tmpPic.g;
        colorBp = tmpPic.b;
    }
    for (unsigned int i = 0; i < height; i++, fwrite(tmp, bufN, 1, fp))
        for (unsigned int j = 0; j < width; j++)
        {
            fwrite(colorBp++, 1, 1, fp);
            fwrite(colorGp++, 1, 1, fp);
            fwrite(colorRp++, 1, 1, fp);
        }
    fclose(fp);
    return 0;
}

int Pixmap::SaveAsGreyBMP8b(const char * fileName) const
{
    if (r == NULL || g == NULL || b == NULL || a == NULL || width == 0 || height == 0 || format == FMT_NULL)
        return 1;
    Pixmap tmpPic;
    if (format == FMT_YUV)
    {
        tmpPic.Load(*this);
        tmpPic.ConvertToRGB();
    }

    FILE* fp = fopen(fileName, "wb");
    if (fp == NULL)
        return 1;
    BmpFileHeader fileHeader;
    BmpFileInformation fileInfo;
    int bufN = (width % 4) ? 4 - width % 4 : 0;
    fileHeader.bfType = 0x4d42;
    fileHeader.bfSize = 54 + 256 * 4 + height*(width + bufN);
    fileHeader.bfReserved1 = fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = 54 + 256 * 4;
    fileInfo.biSize = 40;
    fileInfo.biHeight = height;
    fileInfo.biWidth = width;
    fileInfo.biPlanes = 1;
    fileInfo.biBitCount = 8;
    fileInfo.biCompression = 0;
    fileInfo.biSizeImage = 0;
    fileInfo.biXPelsPerMeter = 0;
    fileInfo.biYPelsPerMeter = 0;
    fileInfo.biClrUsed = 256;
    fileInfo.biClrImportant = 256;

    fwrite(&fileHeader.bfType, 2, 1, fp);
    fwrite(&fileHeader.bfSize, 4, 1, fp);
    fwrite(&fileHeader.bfReserved1, 2, 1, fp);
    fwrite(&fileHeader.bfReserved2, 2, 1, fp);
    fwrite(&fileHeader.bfOffBits, 4, 1, fp);

    fwrite(&fileInfo.biSize, 4, 1, fp);
    fwrite(&fileInfo.biWidth, 4, 1, fp);
    fwrite(&fileInfo.biHeight, 4, 1, fp);
    fwrite(&fileInfo.biPlanes, 2, 1, fp);
    fwrite(&fileInfo.biBitCount, 2, 1, fp);
    fwrite(&fileInfo.biCompression, 4, 1, fp);
    fwrite(&fileInfo.biSizeImage, 4, 1, fp);
    fwrite(&fileInfo.biXPelsPerMeter, 4, 1, fp);
    fwrite(&fileInfo.biYPelsPerMeter, 4, 1, fp);
    fwrite(&fileInfo.biClrUsed, 4, 1, fp);
    fwrite(&fileInfo.biClrImportant, 4, 1, fp);
    UNUM8 palette[4], tmp[4] = { 0 }, color;
    palette[3] = 0;
    for (int i = 0; i < 256; i++)
    {
        palette[0] = palette[1] = palette[2] = i;
        fwrite(&palette, 4, 1, fp);
    }
    const UNUM8 *colorRp = r, *colorGp = g, *colorBp = b;
    if (tmpPic.format == FMT_RGB)
    {
        colorRp = tmpPic.r;
        colorGp = tmpPic.g;
        colorBp = tmpPic.b;
    }
    for (unsigned int i = 0; i < height; i++, fwrite(tmp, bufN, 1, fp))
        for (unsigned int j = 0; j < width; j++)
        {
            color = (UNUM8)(0.3*(*colorRp++) + 0.59*(*colorGp++) + 0.11*(*colorBp++));
            fwrite(&color, 1, 1, fp);
        }

    fclose(fp);
    return 0;
    return 0;
}

int Pixmap::ConvertFormat(unsigned int newFormat, int thre)
{
    switch (newFormat)
    {
    case FMT_NULL:FreePixmap(); return 0; break;
    case FMT_RGB:return ConvertToRGB(); break;
    case FMT_YUV:return ConvertToYUV(); break;
    case FMT_GREY:return ConvertToGrey(); break;
    case FMT_BIN:return ConvertToBin(thre); break;
    default:return 1;
    }
}

int Pixmap::ConvertToYUV()
{
    switch (format)
    {
    case FMT_NULL:return 1;
    case FMT_YUV:return 0;
    case FMT_BIN:
    case FMT_GREY:
    case FMT_RGB:
        UNUM8 *rp = r, *gp = g, *bp = b, cr, cg, cb, y;
        for (unsigned int i = 0; i < width*height; i++)
        {
            cr = *rp;
            cb = *bp;
            cg = *gp;
            *rp++ = y = (UNUM8)(0.3*cr + 0.59*cg + 0.11*cb);
            *gp++ = (UNUM8)(0.87*(0.493*((int)cb - y)) + 127); // 0.87U+127
            *bp++ = (UNUM8)(0.8*(0.877*((int)cr - y)) + 127); //0.8V+127
        }
        format = FMT_YUV;
    }
    return 0;
}

template<typename T> static T ClipToUNUM8(T x)
{
    if (x < 0)
        return 0;
    return (x > 255) ? 255 : x;
}

int Pixmap::ConvertToRGB()
{
    switch (format)
    {
    case FMT_NULL:return 1;
    case FMT_BIN:format = FMT_RGB; return 0;
    case FMT_GREY:format = FMT_RGB; return 0;
    case FMT_RGB:return 0;
    case FMT_YUV:
        UNUM8 *yp = r, *up = g, *vp = b;
        double y, u, v;
        for (unsigned int i = 0; i < width*height; i++)
        {
            y = *yp;
            u = (*up - 127.0) / 0.87;
            v = (*vp - 127.0) / 0.8;
            *yp++ = (UNUM8)ClipToUNUM8(y + 1.14*v);
            *up++ = (UNUM8)ClipToUNUM8(y - 0.39*u - 0.58*v);
            *vp++ = (UNUM8)ClipToUNUM8(y + 2.03*u);
        }
        format = FMT_RGB;
    }
    return 0;
}

int Pixmap::ConvertToGrey()
{
    switch (format)
    {
    case FMT_BIN:	format = FMT_GREY; return 0;
    case FMT_GREY:return 0;
    case FMT_NULL:return 1;
    case FMT_YUV:ConvertToRGB();
    case FMT_RGB:
        UNUM8 cr, cg, cb, *pr = r, *pg = g, *pb = b;
        for (unsigned int i = 0; i < width*height; i++)
        {
            cr = *pr;
            cg = *pg;
            cb = *pb;
            *pr++ = *pg++ = *pb++ = (UNUM8)(0.3*cr + 0.59*cg + 0.11*cb);
        }
        format = FMT_GREY;
    }
    return 0;
}

unsigned char Pixmap::OtsuGetThre()
{
    if (format != FMT_GREY)
        return 0;
    Histogram3c histo(*this, SELECT_R);
    unsigned char thre = 0;
    unsigned int totalPixel = width*height, currCount, currGrey;
    unsigned int  *his = histo.getRHead();
    double w0, w1, u0, u1, max = -1, curr, totalGrey = 0;
    for (unsigned int i = 0; i < 256; i++)
        totalGrey += his[i] * i;
    for (unsigned int i = 0; i < 256; i++)
    {
        w0 = w1 = u0 = u1 = 0.0;
        currCount = currGrey = 0;
        for (unsigned int j = 0; j < i; j++)
        {
            currCount += his[j];
            currGrey += his[j] * j;
        }
        w0 = ((double)currCount) / totalPixel;
        u0 = currGrey ? currGrey / currCount : 0;
        w1 = ((double)totalPixel - currCount) / totalPixel;
        u1 = (totalPixel - currCount) ? (totalGrey - currGrey) / (totalPixel - currCount) : 0;
        curr = w0*w1*(u0 - u1)*(u0 - u1);
        if (curr > max)
        {
            max = curr;
            thre = i;
        }
    }
    return thre;
}

int Pixmap::ConvertToBin(int thre)
{
    switch (format)
    {
    case FMT_BIN:return 0;
    case FMT_NULL:return 1;
    case FMT_YUV:
    case FMT_RGB:ConvertToGrey();
    case FMT_GREY:
        if (thre < 0 || thre>255)
            thre = OtsuGetThre();
        UNUM8 *pr = r, *pg = g, *pb = b;
        for (unsigned int i = 0; i < width*height; i++)
        {
            *pr++ = *pg++ = *pb++ = ((*pr > thre) ? 255 : 0);
        }
        format = FMT_BIN;
    }
    return 0;
}

void Pixmap::ChangeLuma(int del)
{
    del = del > 255 ? 255 : del;
    del = del < -255 ? -255 : del;
    UNUM8 *yp = r;
    unsigned int oldFormat = format;
    ConvertToYUV();
    for (unsigned int i = 0; i < width*height; i++, yp++)
        *yp = (UNUM8)ClipToUNUM8((double)*yp + del);
    ConvertFormat(oldFormat);
}

int Pixmap::InverseColor()
{
    if (format == FMT_NULL)
        return 1;
    int yuvFlag = 0;
    if (format == FMT_YUV)
    {
        yuvFlag = 1;
        ConvertToRGB();
    }
    unsigned char *pr = r, *pg = g, *pb = b;
    for (unsigned int i = 0; i < width*height; i++)
    {
        *pr++ = 255 - *pr;
        *pg++ = 255 - *pg;
        *pb++ = 255 - *pb;
    }
    if (yuvFlag)
        ConvertToYUV();
    return 0;
}

int Pixmap::LogOperation()
{
    if (format == FMT_NULL)
        return 1;
    unsigned int oldFormat = format;
    ConvertToYUV();
    UNUM8 maxLuma = 0, *py = r;
    for (unsigned int i = 0; i < width*height; i++, py++)
        if (*py > maxLuma)
            maxLuma = *py;
    py = r;
    for (unsigned int i = 0; i < width*height; i++)
        *py++ = (UNUM8)(log(*py / 255.0 + 1) / log(maxLuma / 255.0 + 1) * 255);
    ConvertFormat(oldFormat);
    return 0;
}

int Pixmap::HistoEqualizing()
{
    if (format == FMT_NULL)
        return 1;
    unsigned int oldFormat = format;
    ConvertToYUV();
    Histogram3c histo(*this, SELECT_R);
    UNUM8 maxY = 0, minY = 255, *py = r, diffY;
    unsigned int *his = histo.getRHead(), size = width*height;
    if (!size)
        return 1;
    double *hisDis = (double*)malloc(sizeof(double) * 256), *hisCumu = (double*)malloc(sizeof(double) * 256);	//hisDis为该值出现概率 hisCumu为累积概率
    for (unsigned int i = 0; i < 256; i++)
    {
        if (i > maxY&&his[i] > 0)
            maxY = i;
        if (i < minY&&his[i] > 0)
            minY = i;
        hisDis[i] = (double)his[i] / size;
        hisCumu[i] = (i == 0) ? hisDis[i] : hisDis[i] + hisCumu[i - 1];
    }
    diffY = maxY - minY;
    for (unsigned int i = 0; i < size; i++)
        *py++ = (UNUM8)(hisCumu[*py] * diffY + minY);
    ConvertFormat(oldFormat);
    free(hisDis);
    free(hisCumu);
    return 0;
}

Pixel32b Pixmap::NearestInterpolation(double x, double y) const
{
    Pixel32b res;
    res.empty = 1;
    if (x + width / 2 < 0 || y + height / 2 < 0)
        return res;
    unsigned int tarx = (unsigned int)(x + width / 2 + 0.5), tary = (unsigned int)(y + height / 2 + 0.5);
    res = getPixel(tarx, tary);
    return res;
}

Pixel32b Pixmap::BilinearInterpolation(double x, double y) const
{
    Pixel32b res = { 0,0,0,0,1 }, upleft, upright, left, right;
    unsigned int cx = (unsigned int)(x + width / 2), cy = (unsigned int)(y + height / 2);
    if ((unsigned int)(x + width / 2 + 0.5) >= width || (unsigned int)(y + height / 2 + 0.5) >= height || x + width / 2 < 0 || y + height / 2 < 0)
        return res;
    left = getPixel(cx, cy);
    upleft = getPixel(cx, ((cy + 1 >= height) ? (height - 1) : (cy + 1)));
    upright = getPixel(((cx + 1 >= width) ? (width - 1) : (cx + 1)), ((cy + 1 >= height) ? (height - 1) : (cy + 1)));
    right = getPixel(((cx + 1 >= width) ? (width - 1) : (cx + 1)), cy);

    double u = x + width / 2 - (unsigned int)(x + width / 2), v = y + height / 2 - (unsigned int)(y + height / 2);
    res.r = (UNUM8)((1 - u) * (1 - v) * left.r + (1 - u) * v * upleft.r + u * (1 - v) * right.r + u * v *upright.r);
    res.g = (UNUM8)((1 - u) * (1 - v) * left.g + (1 - u) * v * upleft.g + u * (1 - v) * right.g + u * v *upright.g);
    res.b = (UNUM8)((1 - u) * (1 - v) * left.b + (1 - u) * v * upleft.b + u * (1 - v) * right.b + u * v *upright.b);
    res.a = (UNUM8)((1 - u) * (1 - v) * left.a + (1 - u) * v * upleft.a + u * (1 - v) * right.a + u * v *upright.a);
    res.empty = 0;
    return res;
}

int Pixmap::AffineTrans(const shared_ptr<Pixmap>  src, shared_ptr<Pixmap>  dst, double * matrix, int InterpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    if (src == nullptr || dst == nullptr || src == dst)
        return 1;
    double tarx, tary;
    Pixel32b pixel;
    for (int x = -(int)(dst->width / 2); x < (int)(dst->width / 2); x++)
        for (int y = -(int)(dst->height / 2); y < (int)(dst->height / 2); y++)
        {
            tarx = matrix[0] * x + matrix[1] * y + matrix[2];
            tary = matrix[3] * x + matrix[4] * y + matrix[5];
            pixel = (InterpolMethod == 0) ? (src->BilinearInterpolation(tarx, tary)) : (src->NearestInterpolation(tarx, tary));
            if (pixel.empty)
            {
                *(dst->getR(x + dst->width / 2, y + dst->height / 2)) = backR;
                *(dst->getG(x + dst->width / 2, y + dst->height / 2)) = backG;
                *(dst->getB(x + dst->width / 2, y + dst->height / 2)) = backB;
            }
            else
            {
                *(dst->getR(x + dst->width / 2, y + dst->height / 2)) = pixel.r;
                *(dst->getG(x + dst->width / 2, y + dst->height / 2)) = pixel.g;
                *(dst->getB(x + dst->width / 2, y + dst->height / 2)) = pixel.b;
            }
        }
    return 0;
}

shared_ptr<Pixmap>  Pixmap::Translation(double x, double y, int autoExpand, int interpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    shared_ptr<Pixmap> res = nullptr;
    if (autoExpand)
        res = shared_ptr<Pixmap>(new Pixmap((unsigned int)(width + abs(x) * 2), (unsigned int)(height + abs(y) * 2)));
    else
        res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double matrix[9] = { 1,0,-x,0,1,-y,0,0,1 };

    AffineTrans(shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), res, matrix, interpolMethod, backR, backG, backB);
    return res;
}

shared_ptr<Pixmap>  Pixmap::Rotation(double angle, int autoExpand, int interpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    shared_ptr<Pixmap> res = nullptr;
    unsigned int diagonal = (unsigned int)sqrt(width*width + height*height);
    if (autoExpand)
        res = shared_ptr<Pixmap>(new Pixmap(diagonal, diagonal));
    else
        res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double matrix[9] = { cos(angle / 180.0*PI),sin(angle / 180.0*PI),0,-sin(angle / 180.0*PI),cos(angle / 180.0*PI),0,0,0,1 };
    AffineTrans(shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), res, matrix, interpolMethod, backR, backG, backB);
    return res;
}



shared_ptr<Pixmap>  Pixmap::Mirror(int x, int y, int, int interpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    shared_ptr<Pixmap> res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double matrix[9] = { (!x) * 2 - 1.0,0,0,0,(!y) * 2 - 1.0,0,0,0,1 };
    AffineTrans(shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), res, matrix, interpolMethod, backR, backG, backB);
    return res;
}

shared_ptr<Pixmap>  Pixmap::Scale(double x, double y, int autoExpand, int interpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    if (!x || !y)
        return nullptr;
    shared_ptr<Pixmap> res = nullptr;
    if (autoExpand)
        res = shared_ptr<Pixmap>(new Pixmap((unsigned int)(abs(x)*width), (unsigned int)(abs(y)*height)));
    else
        res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double matrix[9] = { 1 / x,0,0,0,1 / y,0,0,0,1 };
    AffineTrans(shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), res, matrix, interpolMethod, backR, backG, backB);
    return res;
}

shared_ptr<Pixmap>  Pixmap::Shear(double x, double y, int autoExpand, int interpolMethod, UNUM8 backR, UNUM8 backG, UNUM8 backB)
{
    shared_ptr<Pixmap> res = nullptr;
    if (autoExpand)
        res = shared_ptr<Pixmap>(new Pixmap((unsigned int)(abs(x)*height + width), (unsigned int)(abs(y)*width + height)));
    else
        res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double matrix[9] = { 1,-x,0,-y,1,0,0,0,1 };
    AffineTrans(shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), res, matrix, interpolMethod, backR, backG, backB);
    return res;
}

shared_ptr<Pixmap> Pixmap::Dilation(const shared_ptr<Pixmap>  stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse) const
{
    if (stElement == nullptr || anchorX >= stElement->width || anchorY >= stElement->height)
        return nullptr;
    shared_ptr<Pixmap> src = shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), stE = stElement;
    shared_ptr<Pixmap> tmpPic1 = nullptr, tmpPic2 = nullptr;
    if (stElement->format != FMT_BIN)
    {
        tmpPic1 = shared_ptr<Pixmap>(new Pixmap(*stE));
        tmpPic1->ConvertToBin();
        stE = tmpPic1;
    }
    if (format != FMT_BIN)
    {
        tmpPic2 = shared_ptr<Pixmap>(new Pixmap(*this));
        tmpPic2->ConvertToBin();
        src = tmpPic2;
    }
    unsigned char value = 255;
    if (inverse)
        value = 0;
    shared_ptr<Pixmap> res = shared_ptr<Pixmap>(new Pixmap(width, height, 255 - value));
    unsigned int stWidth = stE->width, stHeight = stE->height, flag = 0;
    unsigned int stLeft = anchorX, stRight = stWidth - stLeft - 1, stTop = anchorY, stBottom = stHeight - 1 - anchorX;
    for (unsigned int x = stLeft; x < width - stRight; x++)
        for (unsigned int y = stTop; y < height - stBottom; y++)
        {
            flag = 0;
            for (unsigned int stX = x - stLeft; stX < x + stRight&&flag == 0; stX++)
                for (unsigned int stY = y - stTop; stY < y + stBottom&&flag == 0; stY++)
                    if (*(stE->getR(stX - x + stLeft, stY - y + stTop)) == value && *(src->getR(stX, stY)) == value)
                        flag = 1;
            if (flag == 1)
            {
                *(res->getR(x, y)) = value;
                *(res->getG(x, y)) = value;
                *(res->getB(x, y)) = value;
            }
        }
    if (stElement->format != FMT_BIN)
        //delete(tmpPic1)
            ;
    if (format != FMT_BIN)
        //delete(tmpPic2)
            ;
    return res;
}

shared_ptr<Pixmap> Pixmap::Erosion(const shared_ptr<Pixmap>  stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse) const
{
    if (stElement == nullptr || anchorX >= stElement->width || anchorY >= stElement->height)
        return nullptr;
    shared_ptr<Pixmap> src = shared_ptr<Pixmap>(const_cast<Pixmap*>(this)), stE = stElement;
    shared_ptr<Pixmap> tmpPic1 = nullptr, tmpPic2 = nullptr;
    if (stElement->format != FMT_BIN)
    {
        tmpPic1 = shared_ptr<Pixmap>(new Pixmap(*stE));
        tmpPic1->ConvertToBin();
        stE = tmpPic1;
    }
    if (format != FMT_BIN)
    {
        tmpPic2 = shared_ptr<Pixmap>(new Pixmap(*this));
        tmpPic2->ConvertToBin();
        src = tmpPic2;
    }
    unsigned char value = 255;
    if (inverse)
        value = 0;
    shared_ptr<Pixmap> res = shared_ptr<Pixmap>(new Pixmap(width, height, 255 - value));
    unsigned int stWidth = stE->width, stHeight = stE->height, flag = 0;
    unsigned int stLeft = anchorX, stRight = stWidth - stLeft - 1, stTop = anchorY, stBottom = stHeight - 1 - anchorX;
    for (unsigned int x = stLeft; x < width - stRight; x++)
        for (unsigned int y = stTop; y < height - stBottom; y++)
        {
            flag = 1;
            for (unsigned int stX = x - stLeft; stX < x + stRight&&flag == 1; stX++)
                for (unsigned int stY = y - stTop; stY < y + stBottom&&flag == 1; stY++)
                    if (*(stE->getR(stX - x + stLeft, stY - y + stTop)) == value && *(src->getR(stX, stY)) != value)
                        flag = 0;
            if (flag == 1)
            {
                *(res->getR(x, y)) = value;
                *(res->getG(x, y)) = value;
                *(res->getB(x, y)) = value;
            }
        }
    if (stElement->format != FMT_BIN)
        //delete(tmpPic1)
            ;
    if (format != FMT_BIN)
        //delete(tmpPic2)
            ;
    return res;
}

shared_ptr<Pixmap>  Pixmap::Opening(const shared_ptr<Pixmap>  stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse) const
{
    shared_ptr<Pixmap> tmpRes = Erosion(stElement, anchorX, anchorY, inverse), res = nullptr;
    if (tmpRes != nullptr)
        res = tmpRes->Dilation(stElement, anchorX, anchorY, inverse);
    //delete tmpRes;
    return res;
}

shared_ptr<Pixmap>  Pixmap::Closing(const shared_ptr<Pixmap>  stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse) const
{
    shared_ptr<Pixmap> tmpRes = Dilation(stElement, anchorX, anchorY, inverse), res = nullptr;
    if (tmpRes != nullptr)
        res = tmpRes->Erosion(stElement, anchorX, anchorY, inverse);
    //delete tmpRes;
    return res;
}

shared_ptr<Pixmap>  Pixmap::AddBorder(unsigned int borderWidth, int mode) const
{
    if (this->format == FMT_NULL)
        return nullptr;
    shared_ptr<Pixmap> res = shared_ptr<Pixmap>(new Pixmap(width + borderWidth * 2, height + borderWidth * 2));

    res->format=format;
    for (unsigned int x = borderWidth; x < borderWidth + width; x++)
        for (unsigned int y = borderWidth; y < borderWidth + height; y++)
        {
            *(res->getR(x, y)) = *(this->getR(x - borderWidth, y - borderWidth));
            *(res->getG(x, y)) = *(this->getG(x - borderWidth, y - borderWidth));
            *(res->getB(x, y)) = *(this->getB(x - borderWidth, y - borderWidth));
            *(res->getA(x, y)) = *(this->getA(x - borderWidth, y - borderWidth));
        }
    for (unsigned int i = 0; i < borderWidth; i++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            //Top
            *(res->getR(x + borderWidth, borderWidth - i - 1)) = *(this->getR(x, i%height));
            *(res->getG(x + borderWidth, borderWidth - i - 1)) = *(this->getG(x, i%height));
            *(res->getB(x + borderWidth, borderWidth - i - 1)) = *(this->getB(x, i%height));
            *(res->getA(x + borderWidth, borderWidth - i - 1)) = *(this->getA(x, i%height));
            //Buttom
            *(res->getR(x + borderWidth, borderWidth + height + i)) = *(this->getR(x, height - i%height - 1));
            *(res->getG(x + borderWidth, borderWidth + height + i)) = *(this->getG(x, height - i%height - 1));
            *(res->getB(x + borderWidth, borderWidth + height + i)) = *(this->getB(x, height - i%height - 1));
            *(res->getA(x + borderWidth, borderWidth + height + i)) = *(this->getA(x, height - i%height - 1));
        }

        for (unsigned int y = 0; y < height; y++)
        {
            //Left
            *(res->getR(borderWidth - i - 1, y + borderWidth)) = *(this->getR(i%width, y));
            *(res->getG(borderWidth - i - 1, y + borderWidth)) = *(this->getG(i%width, y));
            *(res->getB(borderWidth - i - 1, y + borderWidth)) = *(this->getB(i%width, y));
            *(res->getA(borderWidth - i - 1, y + borderWidth)) = *(this->getA(i%width, y));
            //Right
            *(res->getR(width + borderWidth + i, y + borderWidth)) = *(this->getR(width - i%width - 1, y));
            *(res->getG(width + borderWidth + i, y + borderWidth)) = *(this->getG(width - i%width - 1, y));
            *(res->getB(width + borderWidth + i, y + borderWidth)) = *(this->getB(width - i%width - 1, y));
            *(res->getA(width + borderWidth + i, y + borderWidth)) = *(this->getA(width - i%width - 1, y));

        }

    }
    for (unsigned int x = 0; x < borderWidth; x++)
        for (unsigned int y = 0; y < borderWidth; y++)
        {
            *(res->getR(x, y)) = *(this->getR(0, 0));
            *(res->getR(x + width + borderWidth, y)) = *(this->getR(width - 1, 0));
            *(res->getR(x, y + height + borderWidth)) = *(this->getR(0, height - 1));
            *(res->getR(x + width + borderWidth, y + height + borderWidth)) = *(this->getR(width - 1, height - 1));

            *(res->getG(x, y)) = *(this->getG(0, 0));
            *(res->getG(x + width + borderWidth, y)) = *(this->getG(width - 1, 0));
            *(res->getG(x, y + height + borderWidth)) = *(this->getG(0, height - 1));
            *(res->getG(x + width + borderWidth, y + height + borderWidth)) = *(this->getG(width - 1, height - 1));

            *(res->getB(x, y)) = *(this->getB(0, 0));
            *(res->getB(x + width + borderWidth, y)) = *(this->getB(width - 1, 0));
            *(res->getB(x, y + height + borderWidth)) = *(this->getB(0, height - 1));
            *(res->getB(x + width + borderWidth, y + height + borderWidth)) = *(this->getB(width - 1, height - 1));

            *(res->getA(x, y)) = *(this->getA(0, 0));
            *(res->getA(x + width + borderWidth, y)) = *(this->getA(width - 1, 0));
            *(res->getA(x, y + height + borderWidth)) = *(this->getA(0, height - 1));
            *(res->getA(x + width + borderWidth, y + height + borderWidth)) = *(this->getA(width - 1, height - 1));
        }

    return res;
}


shared_ptr<Pixmap>  Pixmap::Convolution(double * filter, unsigned int filterSize, int normalization, double **outR, double **outG, double **outB) const
{
    if (this->format == FMT_NULL || filter == NULL || !(filterSize % 2))
        return nullptr;
    shared_ptr<Pixmap> src = this->AddBorder(filterSize / 2), res = shared_ptr<Pixmap>(new Pixmap(width, height));
    double *dataR = (double*)malloc(sizeof(double)*width*height);
    double *dataG = (double*)malloc(sizeof(double)*width*height);
    double *dataB = (double*)malloc(sizeof(double)*width*height);
    double tmpR, tmpG, tmpB, tmpA;
    int halfSize = filterSize / 2;
    for (unsigned int x = halfSize; x < halfSize + width; x++)
        for (unsigned int y = halfSize; y < halfSize + height; y++)
        {
            tmpR = tmpG = tmpB = tmpA = 0;
            for (int i = -halfSize; i <= halfSize; i++)
                for (int j = -halfSize; j <= halfSize; j++)
                {
                    tmpR += *(filter + (i + halfSize)*filterSize + j + halfSize)* (*(src->getR((unsigned int)(x + j), (unsigned int)(y + i))));
                    tmpG += *(filter + (i + halfSize)*filterSize + j + halfSize)* (*(src->getG((unsigned int)(x + j), (unsigned int)(y + i))));
                    tmpB += *(filter + (i + halfSize)*filterSize + j + halfSize)* (*(src->getB((unsigned int)(x + j), (unsigned int)(y + i))));
                }
            *(dataR + (y - halfSize)*width + x - halfSize) = tmpR;
            *(dataG + (y - halfSize)*width + x - halfSize) = tmpG;
            *(dataB + (y - halfSize)*width + x - halfSize) = tmpB;
        }
    double minR = INFINITY, maxR = -INFINITY, minG = INFINITY, maxG = -INFINITY, minB = INFINITY, maxB = -INFINITY;
    double *rp = dataR, *gp = dataG, *bp = dataB;
    if (normalization)
    {
        for (unsigned int i = 0; i < width*height; i++, rp++, gp++, bp++)
        {
            if (*rp > maxR) maxR = *rp;
            if (*rp < minR) minR = *rp;
            if (*gp > maxG) maxG = *gp;
            if (*gp < minG) minG = *gp;
            if (*bp > maxB) maxB = *bp;
            if (*bp < minB) minB = *bp;
        }
        rp = dataR;
        gp = dataG;
        bp = dataB;
        double diffR = maxR - minR, diffG = maxG - minG, diffB = maxB - minB;
        for (unsigned int i = 0; i < width * height; i++, rp++, gp++, bp++)
        {
            *rp = (*rp - minR) / diffR * 256;
            *gp = (*gp - minG) / diffG * 256;
            *bp = (*bp - minB) / diffB * 256;
        }
        rp = dataR;
        gp = dataG;
        bp = dataB;
    }
    UNUM8 *resR = res->getRHead(), *resG = res->getGHead(), *resB = res->getBHead(), *resA = res->getAHead();
    const UNUM8 *srcA = this->getAHead();
    for (unsigned int i = 0; i < width*height; i++, rp++, gp++, bp++, resR++, resG++, resB++, resA++, srcA++)
    {
        *resR = (UNUM8)ClipToUNUM8(*rp);
        *resG = (UNUM8)ClipToUNUM8(*gp);
        *resB = (UNUM8)ClipToUNUM8(*bp);
        *resA = *srcA;
    }
    if (outR == NULL)
        delete dataR;
    else
        *outR = dataR;

    if (outG == NULL)
        delete dataG;
    else
        *outG = dataG;

    if (outB == NULL)
        delete dataB;
    else
        *outB = dataB;
    //delete src;
    return res;
}

shared_ptr<Pixmap>  Pixmap::LaplacianEnhance(double * filter, unsigned int filterSize) const
{
    double *inputFilter;
    if (filter == NULL || filterSize == 0)
    {
        inputFilter = (double*)malloc(sizeof(double) * 9);
        for (int i = 0; i < 9; i++)
            inputFilter[i] = 1;
        inputFilter[4] = -8;
        filterSize = 3;
    }
    else
        inputFilter = filter;
    double **outR = (double**)malloc(sizeof(double*)), **outG = (double**)malloc(sizeof(double*)), **outB = (double**)malloc(sizeof(double*));
    shared_ptr<Pixmap> res = Convolution(inputFilter, filterSize, 0, outR, outG, outB);
    if (res == nullptr)
        return nullptr;
    UNUM8 *resR = res->getRHead(), *resG = res->getGHead(), *resB = res->getBHead();
    const UNUM8 *leftR = getRHead(), *leftG = getGHead(), *leftB = getBHead();
    double *tmpR = *outR, *tmpG = *outG, *tmpB = *outB;
    for (unsigned int i = 0; i < width*height;  i++, resR++, resB++, resG++,leftR++, leftG++, leftB++,tmpR++,tmpG++,tmpB++)
    {
        *resR = (UNUM8)ClipToUNUM8(*leftR - *tmpR);
        *resG = (UNUM8)ClipToUNUM8(*leftG - *tmpG);
        *resB = (UNUM8)ClipToUNUM8(*leftB - *tmpB);
    }
    delete *outR;
    delete *outG;
    delete *outB;
    delete outR;
    delete outG;
    delete outB;
    return res;
}

Pixel32b Pixmap::getPixel(unsigned int x, unsigned int y) const
{
    Pixel32b res = { 0,0,0,0,1 };
    if (x >= width || y >= height)
        return res;
    res.empty = 0;
    res.r = *getR(x, y);
    res.g = *getG(x, y);
    res.b = *getB(x, y);
    res.a = *getA(x, y);
    return res;
}

double Pixmap::Gaussian(double x,double r)
{
    const double tmp=pow(2*PI,0.5);
    return pow(2.7182818,-x*x/(2*r*r))/(r*tmp);
}

shared_ptr<Pixmap> Pixmap::BilateralFiltering(int filterSize,double intenPara,double spacePara) const
{
    if (this->format == FMT_NULL)
        return nullptr;
    if(filterSize<0) filterSize=(int)(0.05*pow(width*width+height*height,0.5));
    if(!(filterSize%2)) filterSize++;
    if(spacePara<0) spacePara=0.02*pow(width*width+height*height,0.5);
    if(intenPara<0) intenPara=0.15;
    shared_ptr<Pixmap> src = this->AddBorder(filterSize / 2), res = shared_ptr<Pixmap>(new Pixmap(width, height));
    src->ConvertToYUV();
    res->format=FMT_YUV;
    int halfSize = filterSize / 2;
    double *gauSpace=(double*)malloc(sizeof(double)*filterSize*filterSize);
    double wp,factor,gauInt;
    int gaui=0,i;
    for (int i = -halfSize; i <= halfSize; i++)
        for (int j = -halfSize; j <= halfSize; j++)
            gauSpace[gaui++]=Gaussian(pow(i*i+j*j,0.5),spacePara);
    double srcY,resY=0;
    UNUM8 *dataR=res->getRHead(),*dataG=res->getGHead(),*dataB=res->getBHead(),*dataA=res->getAHead();
    for (unsigned int x = halfSize; x < halfSize + width; x++)
        for (unsigned int y = halfSize; y < halfSize + height; y++)
        {
            srcY=*(src->getR(x,y));
            for (wp=0,gaui=0,resY=0,i = -halfSize; i <= halfSize; i++)
                for (int j = -halfSize; j <= halfSize; j++)
                {
                    gauInt=Gaussian(abs(srcY-(*(src->getR(x+i,y+j))))/255.0,intenPara);
                    factor=gauInt*gauSpace[gaui++];
                    resY+=factor*(*(src->getR(x+i,y+j)));
                    wp+=factor;
                }
            *(dataR+ (y - halfSize)*width + x - halfSize) = (UNUM8)ClipToUNUM8(resY/wp);
            *(dataG + (y - halfSize)*width + x - halfSize) =*(src->getG(x,y));
            *(dataB + (y - halfSize)*width + x - halfSize) =*(src->getB(x,y));
            *(dataA + (y - halfSize)*width + x - halfSize) =*(src->getA(x,y));
        }
    delete gauSpace;
    //delete src;
    res->ConvertFormat(format);
    return res;
}

//----------------------------Pixmap End-----------------------------//
//----------------------------histogram begin------------------------//

#define RANGEOFCOLOR 256

Histogram3c::Histogram3c()
{
    hgR = (unsigned int*)malloc(sizeof(unsigned int)*RANGEOFCOLOR);
    hgG = (unsigned int*)malloc(sizeof(unsigned int)*RANGEOFCOLOR);
    hgB = (unsigned int*)malloc(sizeof(unsigned int)*RANGEOFCOLOR);
    memset(hgR, 0, RANGEOFCOLOR * sizeof(unsigned int));
    memset(hgG, 0, RANGEOFCOLOR * sizeof(unsigned int));
    memset(hgB, 0, RANGEOFCOLOR * sizeof(unsigned int));
}

Histogram3c::Histogram3c(Pixmap & pixmap, unsigned char select):hgR(NULL),hgG(NULL),hgB(NULL)
{
    LoadPixmap(pixmap,select);
}

void Histogram3c::FreeHistogram3c()
{
    free(hgR);
    free(hgG);
    free(hgB);
    hgR = NULL;
    hgB = NULL;
    hgG = NULL;
}

void Histogram3c::LoadPixmap(Pixmap & pixmap, unsigned char select)
{
    FreeHistogram3c();
    unsigned int total = pixmap.GetHeight()*pixmap.GetWidth();
    if (select & 1)
        hgR = CalcHistogram(total, pixmap.getRHead());
    if (select & 2)
        hgG = CalcHistogram(total, pixmap.getGHead());
    if (select & 4)
        hgB = CalcHistogram(total, pixmap.getBHead());
}

unsigned int* Histogram3c::CalcHistogram(unsigned int total, const unsigned char * color)
{
    if (!total)
        return NULL;
    unsigned int *his = (unsigned int*)malloc(sizeof(unsigned int)*RANGEOFCOLOR);
    memset(his,0,sizeof(unsigned int)*RANGEOFCOLOR);
    for (unsigned int i = 0; i < total; i++)
        (his[*color++])++;
    return his;
}

unsigned int Histogram3c::getRCount(unsigned char r) const
{
    if (hgR == NULL)
        return 0;
    return hgR[r];
}

unsigned int Histogram3c::getGCount(unsigned char g) const
{
    if (hgG == NULL)
        return 0;
    return hgG[g];
}

unsigned int Histogram3c::getBCount(unsigned char b) const
{
    if (hgB == NULL)
        return 0;
    return hgB[b];
}

