#include "View/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QTranslator>
#include <src/ViewModel/ViewModel.h>
#include <src/Common/Pixmap32b.h>
#include <src/Common/Histogram3c.h>
#include <QDebug>
#include <iostream>
using namespace std;
#define SPLAHSCREENTIME 2000
void testPixmap32b(){
    char fileName[] = "D:\\1.bmp";
    QImage picQ(fileName);
    Pixmap32b pic(&picQ);

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

    QImage newImage=pic.getQImage();
    newImage.save("QImage.bmp");
    //Test 2
    Pixmap32b copySrc(pic);
    pic.SaveAsBMP24b("src.bmp");
    pic.HistoEqualizing();
    pic.SaveAsBMP24b("Histogram_Equalizing.bmp");
    copySrc.LogOperation();
    copySrc.SaveAsBMP24b("Logarithmic_Operation.bmp");
    cout << "Log and Histogram\n" << endl;
    //Test 3
    /*
    int size, type, inverse = 0;
    size = 1;
    type = 1;//Rect
    sprintf(fileName, "StructureElements\\%d_%d.bmp", size, type);
    inverse = 1;// No
    inverse--;
    Pixmap32b stElement;

    stElement.LoadBmpFile(fileName);
    if (stElement.getFormat() == FMT_NULL)
    {
        qDebug() << "File:" << fileName << "Cannot open" ;
        return ;
    }
    type=1;
    unsigned int anX = stElement.getWidth() / 2, anY = stElement.getHeight() / 2;

    stElement.ConvertToBin(100);
    if (inverse)
        stElement.InverseColor();
    pic.ConvertToBin();
    pic.SaveAsGreyBMP8b("src.bmp");
    stElement.SaveAsGreyBMP8b("StructureElement.bmp");
    Pixmap32b *res = pic.Dilation(&stElement, anX, anY, inverse);
    if (res == NULL)
    {
        qDebug() << "The point is out of the range" ;
        return ;
    }

    res->SaveAsGreyBMP8b("result_dilation.bmp");
    delete res;

    res = pic.Erosion(&stElement, anX, anY, inverse);
    if (res != NULL)
        res->SaveAsGreyBMP8b("result_erosion.bmp");
    delete res;

    res = pic.Opening(&stElement, anX, anY, inverse);
    if (res != NULL)
        res->SaveAsGreyBMP8b("result_opening.bmp");
    delete res;

    res = pic.Closing(&stElement, anX, anY, inverse);
    if (res != NULL)
        res->SaveAsGreyBMP8b("result_closing.bmp");
    delete res;
    qDebug() << "Morphology Ok!\n";*/
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
    testPixmap32b();

    pMainWindows->show();
    return a.exec();
}
