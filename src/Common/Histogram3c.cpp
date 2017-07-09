#include "Histogram3c.h"

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

Histogram3c::Histogram3c(Pixmap32b & pixmap, unsigned char select):hgR(NULL),hgG(NULL),hgB(NULL)
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

void Histogram3c::LoadPixmap(Pixmap32b & pixmap, unsigned char select)
{
	FreeHistogram3c();
	unsigned int total = pixmap.getHeight()*pixmap.getWidth();
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

