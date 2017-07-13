#include "newcanvasdialog.h"
#include "ui_newcanvasdialog.h"

Params NewCanvasDialog::params;

NewCanvasDialog::NewCanvasDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCanvasDialog)
{
    ui->setupUi(this);
    connect(ui->acceptButton,SIGNAL(pressed()),this,SLOT(AcceptButton()));
    connect(ui->rejectButton,SIGNAL(pressed()),this,SLOT(RejectButton()));
}


Params NewCanvasDialog::GetCanvasSize(QWidget *parent)
{
    NewCanvasDialog *tmpWidget=new NewCanvasDialog(parent);
    params.Clear();
    params.setType(RESULT::REJECTED);
    tmpWidget->exec();
    delete tmpWidget;
    return params;
}

NewCanvasDialog::~NewCanvasDialog()
{
    delete ui;
}

void NewCanvasDialog::AcceptButton()
{

    params.Clear();
    params.setType(RESULT::ACCEPTED);
    params.setInts({ui->widthSpinBox->value(),ui->heightSpinBox->value()});
    this->close();
}


void NewCanvasDialog::RejectButton()
{
    params.Clear();
    params.setType(RESULT::REJECTED);
    params.setInts({ui->widthSpinBox->value(),ui->heightSpinBox->value()});
    this->close();
}
