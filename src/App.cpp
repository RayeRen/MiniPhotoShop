//
// Created by Raye on 2017/7/6.
//
#include <iostream>
#include "ViewModel/ViewModel.h"
#include "View/MainWindows.h"

using namespace std;
int main(){
    shared_ptr<ViewModel> pViewModel(new ViewModel);
    shared_ptr<Model> pModel(new Model);
    shared_ptr<MainWindows> pMainWindows(new MainWindows);

    //add viewModel to the observer list of model
    pModel->addObserver(pViewModel);
    //add view to the observer list of viewModel.
    pViewModel->addObserver(pMainWindows);

    //bind the commands
    pMainWindows->setAddLineCommand(pViewModel->getAddLineCommand());

}
