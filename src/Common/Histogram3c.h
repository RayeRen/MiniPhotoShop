/*
*	Histogram3c类 3通道直方图
*/
#ifndef HISTOGRAM3C_H
#define HISTOGRAM3C_H

#include "Pixmap32b.h"

enum {SELECT_R=1,SELECT_G=2,SELECT_B=4,SELECT_GREY=8};	//标记需要计数的通道

class Histogram3c
{
	unsigned int *hgR, *hgG, *hgB;	//3通道颜色计数
public:
	Histogram3c();
	Histogram3c(Pixmap32b &pixmap,unsigned char select=SELECT_R|SELECT_G|SELECT_B);
	~Histogram3c() { FreeHistogram3c(); }
	void FreeHistogram3c();
	void LoadPixmap(Pixmap32b &pixmap, unsigned char select = SELECT_R | SELECT_G | SELECT_B);	//对Pixmap32b类计算直方图
	unsigned int* CalcHistogram(unsigned int total,const unsigned char *color);
	unsigned int getRCount(unsigned char r) const;
	unsigned int getGCount(unsigned char g) const;
	unsigned int getBCount(unsigned char b) const;
	unsigned int *getRHead() { return hgR; }
	unsigned int *getGHead() { return hgG; }
	unsigned int *getBHead() { return hgB; }
};

#endif
