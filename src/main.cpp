#include "View/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QTranslator>
#include <src/ViewModel/ViewModel.h>
#include <QDebug>
#include <iostream>
using namespace std;
#define SPLAHSCREENTIME 2000


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator tran;
    tran.load("qt_zh_CN.qm",":/langs/trans");
    a.installTranslator(&tran);

    shared_ptr<Model> pModel(new Model());
    shared_ptr<ViewModel> pViewModel(new ViewModel(pModel));
    shared_ptr<MainWindow> pMainWindows(new MainWindow);
    StateManager::Init();
    StateManager::SetpMainWindow(pMainWindows.get());
    //add viewModel to the observer list of model
    pModel->addObserver(pViewModel);
    //add view to the observer list of viewModel.
    pViewModel->addObserver(pMainWindows);

    //bind
    pMainWindows->setAddLineCommand(pViewModel->getAddLineCommand());
    pMainWindows->setAddEllipseCommand(pViewModel->getAddEllipseCommand());
    pMainWindows->setAddRectCommand(pViewModel->getAddRectCommand());
    pViewModel->SetLayouts(pModel->GetLayouts());
    pViewModel->SetPen(pModel->GetPen());
    pViewModel->SetBrush(pModel->GetBrush());
    pMainWindows->SetPen(pViewModel->GetPen());
    pMainWindows->SetBrush(pViewModel->GetBrush());
    pMainWindows->SetDisplayImage(pViewModel->GetDisplayImage());
    pMainWindows->setNewCanvasCommand(pViewModel->getNewCanvasCommand());
    pMainWindows->setPenUpdateCommand(pViewModel->getPenUpdateCommand());
    pMainWindows->setBrushUpdateCommand(pViewModel->getBrushUpdateCommand());
    pMainWindows->setChangeSelectedCommand(pViewModel->getChangeSelectedCommand());
    pMainWindows->setAddPicCommand(pViewModel->getAddPicCommand());
    pMainWindows->setLayoutTransCommand(pViewModel->getLayoutTransCommand());
    pMainWindows->setLayoutTransNotifyCommand(pViewModel->getLayoutTransNotifyCommand());
    pMainWindows->setLoadProjectCommand(pViewModel->getloadProjectCommand());
    pMainWindows->setSaveProjectCommand(pViewModel->getsaveProjectCommand());
    pMainWindows->setNewProjectCommand(pViewModel->getNewProjectCommand());
    pMainWindows->setUndoCommand(pViewModel->getUndoCommand());
    pMainWindows->setRedoCommand(pViewModel->getRedoCommand());
    pMainWindows->setDeleteLayoutCommand(pViewModel->getDeleteLayoutCommand());
    pMainWindows->setSaveAsPictureCommand(pViewModel->getSaveAsPictureCommand());
    pMainWindows->setLayoutOrderChangeCommand(pViewModel->getLayoutOrderChangeCommand());
    pMainWindows->setPixmapFilterCommand(pViewModel->getPixmapFilterCommand());
    QSplashScreen *screen=new QSplashScreen(QPixmap(":/img/img/SplashScreen.png"));
    screen->show();
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < SPLAHSCREENTIME)
        a.processEvents();
    delete screen;

    pMainWindows->show();
    pMainWindows->ShowHelp();
    return a.exec();
}
