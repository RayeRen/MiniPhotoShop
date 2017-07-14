## DataStructure Docs
## 画笔
```cpp

class Pen {
    unsigned char foreR, foreG, foreB;  //foreR,foreG,foreB代表画笔的颜色
    int penStyle, lineWidth;
    //penStyle代表画笔样式
    //lineWidth代表线宽
  }
 ```
 ## 画刷
 ```cpp
class Brush {
     unsigned char backR, backG, backB; //画刷颜色
     int brushStyle;                    //画刷样式
 }
  ```
 
## 形状抽象类
```cpp
class BaseShape {
//Member
    int posX, posY;     //posX,posY代表该形状的X,Y值
    int type;           //type代表该形状的类型
    string name;        //name代表该形状的名字
    double scaleX, scaleY, angle; 
    //scaleX,scaleY代表该形状的X、Y缩放率
    //angle代表该形状的旋转角度 
//Public Methods:
    void Move(int x ,int y);                //形状平移
    void Scale(double scaleX,double scaleY);//形状缩放
    void Rotate(double angle);              //形状旋转
}
```

## 线
```cpp
class Line : public BaseShape {
    Pen pen;                //Line的画笔
    int x1, y1, x2, y2;     //Line的两个端点的坐标
}
```

## 椭圆
```cpp
class Ellipse:public BaseShape
{
    Pen pen;    //画笔
    Brush brush;//画刷
    int a,b;    //a代表x轴分量，b代表y轴分量。
}
```

## 矩形
```cpp
class Rect:public BaseShape
{
    Pen pen;            //画笔
    Shape shape;        //画刷
    int width,height;   //长宽
}
```



## 位图
```cpp
class Pixmap:public BaseShape
{
//Member
    unsigned int height, width, format;	    //height为图像高度 width为图像宽度 format为状态
    UNUM8 *r, *g, *b, *a;	                //r、g、b、a为4个通道的数组 顺序为从左下到右上，先行后列
//Public Methods:
    int Load(const Pixmap &pixmap);         //加载位图
    int Load(const QImage &image);          //加载位图
    void FreePixmap();	                    //清空数据
    shared_ptr<QImage> Output();            //输出QImage

    int ConvertFormat(unsigned int newFormat, int thre=-1);	//转换格式
    int ConvertToYUV();     //转化为YUV颜色格式
    int ConvertToRGB();     //转化为RGB颜色格式
    int ConvertToGrey();	//用YUV中的Y通道填充RGB，转换为灰阶图像
    unsigned char OtsuGetThre();	//获得大津法阈值
    int ConvertToBin(int thre=-1);	//二值化，若thre不在0~255之间，则先进行大津法求阈值操作
    void ChangeLuma(int del);	//改变YUV通道中的Y值，并恢复原格式
    int InverseColor();	//反色
    int LogOperation();	//对数操作
    int HistoEqualizing();	//直方图均衡
    static double Gaussian(double x,double r);//计算高斯分布


    shared_ptr<Pixmap> AddBorder(unsigned int borderWidth,int mode=0) const;	//镜像边缘扩展
    shared_ptr<Pixmap> Convolution(double * filter, unsigned int filterSize, int normalization=1,double **outR=NULL,double **outG=NULL,double **outB=NULL) const;	//卷积
    shared_ptr<Pixmap> ConvolutionGet(double * filter, unsigned int filterSize, int normalization=1,double **outR=NULL,double **outG=NULL,double **outB=NULL);	//卷积
    shared_ptr<Pixmap> LaplacianEnhance(double * filter=NULL, unsigned int filterSize=0) ;	//拉普拉斯图像增强
    shared_ptr<Pixmap> BilateralFiltering(int filterSize=-1,double intenPara=-1,double spacePara=-1) ;//双边滤波
};
```
## 直方图
```cpp
class Histogram3c
{
//Member
    unsigned int *hgR, *hgG, *hgB;	//3通道颜色计数
//public methods
    void FreeHistogram3c();         //清理数据
    void LoadPixmap(Pixmap &pixmap, unsigned char select = PIXMAP::SELECT_R|PIXMAP::SELECT_G|PIXMAP::SELECT_B);	//对Pixmap类计算直方图
    unsigned int* CalcHistogram(unsigned int total,const unsigned char *color); //计算直方图
};
```

## 图层
```cpp
class Layouts
{
    vector<shared_ptr<BaseShape>>list;  //图层链表
}
```
## 日志
```cpp
class DoneInfo{
    int layoutindex,beforelayoutindex;              //图层位置信息
    shared_ptr<BaseShape> aftershape,beforeshape;   //形状信息
    int commandtype;                                //命令类型
}
```

注：以上介绍省略了成员的Get方法和Set方法。