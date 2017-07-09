#include "View/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include<QTranslator>
#include <src/ViewModel/ViewModel.h>
#include <src/Common/Pixmap32b.h>
#include <src/Common/Histogram3c.h>
#include <QDebug>
#include <iostream>
using namespace std;
#define SPLAHSCREENTIME 2000
void testPixmap32b(){
    char fileName[] = "D:\\1.bmp";
    Pixmap32b pic(fileName);

    if (pic.getFormat() == FMT_NULL)
    {
        cout << "文件打开失败" << endl;
        return ;
    }
    //Test 1
    if (!pic.SaveAsBMP24b("original_pic.bmp"))
        cout << "\n原图已输出至程序根目录下 original_pic.bmp 文件" << endl;

    if (!pic.SaveAsGreyBMP8b("result_greyscale.bmp"))
        cout << "\n8位灰度图已输出至程序根目录下 result_greyscale.bmp 文件" << endl;

    int delY=10;
    cout << "\n请输入Y值变化量(有效范围-255~255):10" << endl;

    pic.ChangeLuma(delY);

    if (!pic.SaveAsBMP24b("result_Ychanged.bmp"))
        cout << "\nY值改变之后的24位图已输出至程序根目录下 result_Ychanged.bmp 文件\n" << endl;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator tran;
    tran.load("qt_zh_CN.qm",":/langs/trans");
    a.installTranslator(&tran);

    shared_ptr<Model> pModel(new Model());
    shared_ptr<ViewModel> pViewModel(new ViewModel(pModel));
    shared_ptr<MainWindow> pMainWindows(new MainWindow);

    //add viewModel to the observer list of model
    pModel->addObserver(pViewModel);
    //add view to the observer list of viewModel.
    pViewModel->addObserver(pMainWindows);

    //bind
    pMainWindows->setAddLineCommand(pViewModel->getAddLineCommand());
    pMainWindows->setAddEllipseCommand(pViewModel->getAddEllipseCommand());

    pViewModel->SetLayouts(pModel->GetLayouts());
    pMainWindows->SetPen(pModel->GetPen());
    pMainWindows->SetBrush(pModel->GetBrush());
    pMainWindows->SetDisplayImage(pViewModel->GetDisplayImage());
    pMainWindows->setNewCanvasCommand(pViewModel->getNewCanvasCommand());
    pMainWindows->setPenUpdateCommand(pViewModel->getPenUpdateCommand());

    QSplashScreen *screen=new QSplashScreen(QPixmap(":/img/img/SplashScreen.png"));
    screen->show();
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < SPLAHSCREENTIME)
        a.processEvents();
    delete screen;

    //Test For Pixmap32b.h
    testPixmap32b();

    pMainWindows->show();
    return a.exec();
}
