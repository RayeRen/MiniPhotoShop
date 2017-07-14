## ViewModel Docs

### Commands

> addLineCommand

添加直线

> addEllipseCommand

添加椭圆

> addRectCommand

添加矩形

> newCanvasCommand

增加新画布

> penUpdateCommand,

更新画笔类型

> brushUpdateCommand,

更新填充类型

> newProjectCommand,

新增项目

> saveProjectCommand,

保存项目

> loadProjectCommand,

读入项目

> changeSelectedCommand,

改变选择图层

> addPicCommand,

新增图片

> layoutTransCommand,

图层操作

> undoCommand,

撤销

> redoCommand,

重做

> layoutTransNotifyCommand,

图层操作通知

> deleteLayoutCommand,

删除图层

> saveAsPictureCommand,

保存图片

> layoutOrderChangeCommand,

改变图层顺序

> pixmapFilterCommand;

滤镜

### Public 方法

```cpp
void ViewModel::SaveAsPicture(string path)
```

保存图片图层

```cpp
void RefreshDisplayImage(int index=-1)
```

重新渲染图像，保存在viewmodel内存空间中

```cpp
void NewCanvas(unsigned int width,unsigned int height)
```

新建画布

```cpp
void SetSelectedLayout(int selectedLayout)
```

设置选择的图层

```cpp
void SetPen(const Pen* pen)
```

设置画笔

```cpp
void SetBrush(const Brush* brush)
```

设置笔刷

```cpp
void LayoutMove(int x,int y)
```

移动图层

```cpp
void LayoutRotate(double angle);
```

旋转图层

```cpp
void LayoutScale(double scaleX,double scaleY);
```

缩放图层

```cpp
void ClearViewModel()
```

清空ViewModel画布