#include "View/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <src/ViewModel/ViewModel.h>

#define SPLAHSCREENTIME 2000

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

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
    pMainWindows->SetDisplayImage(pViewModel->GetDisplayImage());
    pMainWindows->setNewCanvasCommand(pViewModel->getNewCanvasCommand());


    QSplashScreen *screen=new QSplashScreen(QPixmap(":/img/img/SplashScreen.png"));
    screen->show();
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < SPLAHSCREENTIME)
        a.processEvents();
    delete screen;

    pMainWindows->show();
    return a.exec();
}
