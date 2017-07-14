#include "newcanvascommand.h"
#include "../ViewModel.h"

NewCanvasCommand::NewCanvasCommand(const shared_ptr<Model> &pModel, const shared_ptr<ViewModel> &pViewModel) : BaseCommand(pModel,pViewModel) {}

void NewCanvasCommand::exec()
{
    vector<int> ints=params.getInts();
    qDebug()<<"NEW_CANVAS"<<ints[0]<<ints[1];
    pViewModel->NewCanvas(ints[0],ints[1]);
    pModel->newProject(ints[0],ints[1]);
}
