#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qdebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    state=STATE::INIT;
    pen=NULL;
    brush=NULL;
    displayImage=NULL;
    ui->setupUi(this);
    ui->MainDisplayWidget->SetState(&state);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand)
{
    ui->MainDisplayWidget->setAddLineCommand(addLineCommand);
}

void MainWindow::update(Params params)
{

}

void MainWindow::SetPen(const Pen* pen)
{
    this->pen=pen;

    ui->MainDisplayWidget->SetPen(pen);
}

void MainWindow::SetBrush(const Brush* brush)
{
    this->brush=brush;
}

void MainWindow::SetDisplayImage(const QImage* displayImage)
{
    this->displayImage=displayImage;
    ui->MainDisplayWidget->SetImage(displayImage);
}

void MainWindow::setNewCanvasCommand(const shared_ptr<BaseCommand> &newCanvasCommand)
{
    this->newCanvasCommand=newCanvasCommand;
    ui->MainDisplayWidget->setNewCanvasCommand(newCanvasCommand);
    Params params;
    params.setInts({ui->MainDisplayWidget->getRealWidth(),ui->MainDisplayWidget->getRealHeight()});
    newCanvasCommand->setParams(params);
    newCanvasCommand->exec();
}
