# MiniPhotoShop 项目报告 Part1

### 编写者

姓名：任意 

学号：3150103692

### 报告内容

- 整体架构设计
- Common模块
- ViewModel非图像渲染部分
- 持续集成



## 架构设计

Mini PhotoShop采用MVVM架构实现，如下图所示

![ry1](C:\Users\Raye\OneDrive - zju.edu.cn\University\Study\17summer\MiniPhotoShop\doc\pic\ry1.png)

#### 各模块职责如下

- Model
   - 保存图层数据，当前画笔等参数
- ViewModel
   - 将model中的各个图层整合成一张可显示的图片
- View
   - UI布局
   - 显示ViewModel整合完毕的图片

#### 各模块之间的交互使用以下机制

- View --> VIewModel
  - 使用命令模式，在view中调用指定命令的exec方法，在各个命令的方法中实现对ViewModel的访问和修改。
- ViewModel --> Model
  - 在顶层模块中将Model指针绑定给ViewModel，在命令中调用Model的对应方法修改Model。
- Model --> ViewModel
  - Model作为被观察者，ViewModel作为观察者，监听Model的改变。一旦Model改变，通知ViewModel重新渲染图层。
- ViewModel --> View
  - ViewModel作为被观察者，View作为观察者，监听ViewModel的改变。一旦ViewModel改变，通知View获取新渲染好的图片进行显示。



## 文件结构组织

- MiniPhotoShop
  - doc <u>文档</u>
  - img <u>图片资源</u>
  - src <u>源代码目录</u>
    - Common
    - Model
    - View
    - ViewModel
    - `Constants.h`  <u>常量</u>
    - `main.cpp`  <u>顶层模块</u>
  - trans <u>国际化配置文件</u>
  - `.gitignore`
  - `LISENCE` 
  - `MiniPhotoShop.pro` <u>qt配置文件</u>
  - `README.md` 
  - `imgs.qrc` <u>qt所需图片资源文件</u>
  - `langs.qrc` <u>qt所需国际化文件</u>



# 各模块

