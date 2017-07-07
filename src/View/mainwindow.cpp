#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand) {
    MainWindow::addLineCommand = addLineCommand;
}

void MainWindow::update(Params params) {

}
