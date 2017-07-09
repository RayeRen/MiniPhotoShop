/*
*	Pixmap32b类 32位位图
*	支持RGB、YUV颜色格式以及灰阶、二值图像格式
*/
#ifndef PIXMAP32B_H
#define PIXMAP32B_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <QImage>
#include "DataStructure.h"
typedef unsigned char UNUM8;	//8位无符号数
typedef unsigned short UNUM16;	//16位无符号数
typedef unsigned int UNUM32;	//32位无符号数
typedef signed char SNUM8;		//8位有符号数
typedef signed short SNUM16;	//16位有符号数
typedef signed int SNUM32;		//32位有符号数

enum { FMT_NULL, FMT_RGB, FMT_YUV,FMT_GREY,FMT_BIN};	//表示Pixmap32b状态 FMT_NULL为无数据 FMT_RGB为RGBA格式数据 FMT_YUV为YUV格式数据(YUV分别对应r,b,g数组) FMT_BIN为二值图像（RGBA方式存储）

typedef struct {
	UNUM8 r, g, b, a,empty;
}Pixel32b;

class Pixmap32b:public BaseShape
{
	unsigned int height, width, format;	//height为图像高度 width为图像宽度 format为状态
	UNUM8 *r, *g, *b, *a;	//r、g、b、a为4个通道的数组 顺序为从左下到右上，先行后列
public:
    Pixmap32b(const char* fileName = NULL) : BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL) { LoadBmpFile(fileName); }	//从图片文件载入
	Pixmap32b(unsigned int width, unsigned int height,unsigned char value=0);	//新建height*width大小，初始颜色为黑色的图片，RGB格式
    Pixmap32b(const Pixmap32b &pixmap) :BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL) { Load(pixmap); }//拷贝构造函数
    Pixmap32b(const QImage *image):BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL){
        if(image->format()!=QImage::Format_ARGB32){
            QImage *newimage=&(image->convertToFormat(QImage::Format_ARGB32,image->colorTable()));
            LoadQImage(newimage);
            delete newimage;
        }else{
            LoadQImage(image);
        }
    }

    ~Pixmap32b() { FreePixmap32b(); }

    int LoadQImage(const QImage *image);
    QImage getQImage();

	int LoadBmpFile(const char * fileName);	//尝试从图片文件载入数据
	int Load(const Pixmap32b &pixmap);	//拷贝构造函数
	int SaveAsBMP24b(const char * fileName) const;	//存储为24位BMP图片
	int SaveAsGreyBMP8b(const char * fileName) const;	//存储为8位灰度图片
	void FreePixmap32b();	//清空数据

	int ConvertFormat(unsigned int newFormat, int thre=-1);	//转换格式
	int ConvertToYUV();	//转化为YUV颜色格式
	int ConvertToRGB();	//转化为RGB颜色格式
	int ConvertToGrey();	//用YUV中的Y通道填充RGB，转换为灰阶图像
	unsigned char OtsuGetThre();	//获得大津法阈值
	int ConvertToBin(int thre=-1);	//二值化，若thre不在0~255之间，则先进行大津法求阈值操作
	void ChangeLuma(int del);	//改变YUV通道中的Y值，并恢复原格式
	int InverseColor();	//反色
	int LogOperation();	//对数操作
	int HistoEqualizing();	//直方图均衡
	Pixel32b NearestInterpolation(double x,double y) const;	//最邻近插值
	Pixel32b BilinearInterpolation(double x,double y) const;	//双线性插值
	static double Gaussian(double x,double r);//计算高斯分布 
	
	static int AffineTrans(const Pixmap32b *src,Pixmap32b *dst,double *matrix, int interpolMethod=0,UNUM8 backR=255,UNUM8 backG=255,UNUM8 backB=255);	//根据矩阵进行仿射变换  坐标(x,y,1)转置 matrix 3*3矩阵顺序 (1,1) (1,2) (1,3) (2,1) (2,2) (2,3) (3,1) (3,2) (3,3)
	Pixmap32b *Translation(double x,double y,int autoExpand=1,int interpolMethod=0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//平移
	Pixmap32b *Rotation(double angle, int autoExpand = 1,int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//旋转
	Pixmap32b *Mirror(int x,int y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//镜像
	Pixmap32b *Scale(double x, double y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//缩放
	Pixmap32b *Shear(double x, double y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//斜切

	Pixmap32b *Dilation(const Pixmap32b *stElement,unsigned int anchorX,unsigned int anchorY,unsigned int inverse=0) const;	//膨胀
	Pixmap32b *Erosion(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse=0) const;	//腐蚀
	Pixmap32b *Opening(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse = 0) const;	//开运算
	Pixmap32b *Closing(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse = 0) const;	//闭运算

	Pixmap32b *AddBorder(unsigned int borderWidth,int mode=0) const;	//镜像边缘扩展
	Pixmap32b *Convolution(double * filter, unsigned int filterSize, int normalization=1,double **outR=NULL,double **outG=NULL,double **outB=NULL) const;	//卷积
	Pixmap32b *LaplacianEnhance(double * filter=NULL, unsigned int filterSize=0) const;	//拉普拉斯图像增强
	Pixmap32b *BilateralFiltering(int filterSize=-1,double intenPara=-1,double spacePara=-1) const;//双边滤波 

	unsigned int getWidth() const { return width; }	//返回图片宽度
	unsigned int getHeight() const { return height; }	//返回图片高度

	const unsigned char *getRHead() const { return r; }	//返回r数组
	const unsigned char *getGHead() const { return g; }	//返回g数组
	const unsigned char *getBHead() const { return b; }	//返回b数组
	const unsigned char *getAHead() const { return a; }	//返回a数组

	unsigned char *getRHead() { return r; }	//非常量版 返回r数组
	unsigned char *getGHead() { return g; }	//非常量版 返回g数组
	unsigned char *getBHead() { return b; }	//非常量版 返回b数组
	unsigned char *getAHead() { return a; }	//非常量版 返回a数组

	unsigned int getFormat() const { return format; }	//返回格式

	const unsigned char *getR(unsigned int x, unsigned int y) const { if (x < width&&y < height) return r + y*width + x; return NULL; }//返回(x,y)坐标处的r值指针
	const unsigned char *getG(unsigned int x, unsigned int y) const { if (x < width&&y < height)return g + y*width + x; return NULL; } //返回(x,y)坐标处的g值指针
	const unsigned char *getB(unsigned int x, unsigned int y) const { if (x < width&&y < height) return b + y*width + x; return NULL; } //返回(x,y)坐标处的b值指针
	const unsigned char *getA(unsigned int x, unsigned int y) const { if (x < width&&y < height) return a + y*width + x; return NULL; } //返回(x,y)坐标处的a值指针
	Pixel32b getPixel(unsigned int x,unsigned int y) const;	//获得(x,y)处的像素点颜色
	
	unsigned char *getR(unsigned int x, unsigned int y) { if (x < width&&y < height) return r + y*width + x; return NULL; } //非常量版 返回(x,y)坐标处的r值指针
	unsigned char *getG(unsigned int x, unsigned int y) { if (x < width&&y < height) return g + y*width + x; return NULL; }//非常量版 返回(x,y)坐标处的g值指针
	unsigned char *getB(unsigned int x, unsigned int y) { if (x < width&&y < height) return b + y*width + x; return NULL; }//非常量版 返回(x,y)坐标处的b值指针
	unsigned char *getA(unsigned int x, unsigned int y) { if (x < width&&y < height) return a + y*width + x; return NULL; }//非常量版 返回(x,y)坐标处的a值指针

};

#endif
