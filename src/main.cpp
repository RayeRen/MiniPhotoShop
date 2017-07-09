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
        cout << "Open File Failed" << endl;
        return ;
    }
    //Test 1
    if (!pic.SaveAsBMP24b("original_pic.bmp"))
        qDebug() << QStringLiteral(" original_pic.bmp is created");

    if (!pic.SaveAsGreyBMP8b("result_greyscale.bmp"))
        qDebug() << QStringLiteral("8 bit grayscale: result_greyscale.bmp " );

    int delY=10;
    qDebug() << QStringLiteral("delY= 10");

    pic.ChangeLuma(delY);

    if (!pic.SaveAsBMP24b("result_Ychanged.bmp"))
        qDebug() << QStringLiteral("Ychanged: result_Ychanged.bmp");
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
    pMainWindows->setAddRectCommand(pViewModel->getAddRectCommand());
    pViewModel->SetLayouts(pModel->GetLayouts());
    pMainWindows->SetPen(pModel->GetPen());
    pMainWindows->SetBrush(pModel->GetBrush());
    pMainWindows->SetDisplayImage(pViewModel->GetDisplayImage());
    pMainWindows->setNewCanvasCommand(pViewModel->getNewCanvasCommand());
    pMainWindows->setPenUpdateCommand(pViewModel->getPenUpdateCommand());
    pMainWindows->setBrushUpdateCommand(pViewModel->getBrushUpdateCommand());
    QSplashScreen *screen=new QSplashScreen(QPixmap(":/img/img/SplashScreen.png"));
    screen->show();
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < SPLAHSCREENTIME)
        a.processEvents();
    delete screen;

    //Test For Pixmap32b.h
    //testPixmap32b();

    pMainWindows->show();
    return a.exec();
}
