#include "View/mainwindow.h"
#include <QApplication>
#include <src/ViewModel/ViewModel.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    shared_ptr<Model> pModel(&Model::getInstance());
    shared_ptr<ViewModel> pViewModel(&ViewModel::getInstance(pModel));
    shared_ptr<MainWindow> pMainWindows(new MainWindow);

    //add viewModel to the observer list of model
    pModel->addObserver(pViewModel);
    //add view to the observer list of viewModel.
    pViewModel->addObserver(pMainWindows);

    //bind the commands
    pMainWindows->setAddLineCommand(pViewModel->getAddLineCommand());
    pMainWindows->setAddEllipseCommand(pViewModel->getAddEllipseCommand());
    pMainWindows->SetPen(pModel->GetPen());
    pMainWindows->show();
    pMainWindows->SetDisplayImage(pViewModel->GetDisplayImage());
    pMainWindows->setNewCanvasCommand(pViewModel->getNewCanvasCommand());
    pViewModel->SetLayouts(pModel->GetLayouts());

    return a.exec();
}
