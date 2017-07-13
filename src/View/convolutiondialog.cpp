#include "convolutiondialog.h"
#include "ui_convolutiondialog.h"

Params ConvolutionDialog::params;

ConvolutionDialog::ConvolutionDialog(QWidget *parent,int defaultValue) :
    QDialog(parent),
    ui(new Ui::ConvolutionDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(ui->sizeSpinBox->value());
    ui->tableWidget->setColumnCount(ui->sizeSpinBox->value());
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    int size=3;
    ui->sizeSpinBox->setValue(size);
    QTableWidgetItem *item;
    for(int i=0;i<size;i++)
    {
        ui->tableWidget->setRowHeight(i,(ui->tableWidget->height()*0.9)/size);
        ui->tableWidget->setColumnWidth(i,(ui->tableWidget->width()*0.9)/size);
        for(int j=0;j<size;j++)
        {
            if(defaultValue==PIXMAP::LAPLACIANENHANCE&&i==1&&j==1)
                item=new QTableWidgetItem(QString("-8"));
            else
                item=new QTableWidgetItem(QString("1"));
            ui->tableWidget->setItem(i,j,item);
        }
    }
    connect(ui->acceptButton,SIGNAL(pressed()),this,SLOT(AcceptButtonPressed()));
    connect(ui->rejectButton,SIGNAL(pressed()),this,SLOT(RejectButtonPressed()));
    connect(ui->sizeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(SizeChanged(int)));
    params.Clear();
    params.setType(RESULT::REJECTED);
}

Params ConvolutionDialog::GetConvolutionCore(QWidget *parent,int defaultValue)
{
    ConvolutionDialog *tmpDialog=new ConvolutionDialog(parent,defaultValue);
    tmpDialog->exec();
    delete tmpDialog;
    return params;
}

ConvolutionDialog::~ConvolutionDialog()
{
    delete ui;
}

void ConvolutionDialog::AcceptButtonPressed()
{
    params.Clear();
    params.setType(RESULT::ACCEPTED);
    int size=ui->sizeSpinBox->value();
    params.setInts({ui->sizeSpinBox->value()});
    vector<double> doubles;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            doubles.push_back(((ui->tableWidget->item(i,j))->text()).toDouble());
        }
    params.setDoubles(doubles);
    this->close();
}

void ConvolutionDialog::RejectButtonPressed()
{
    params.Clear();
    params.setType(RESULT::REJECTED);

    this->close();
}

void ConvolutionDialog::SizeChanged(int size)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(size);
    ui->tableWidget->setColumnCount(size);
    for(int i=0;i<size;i++)
    {
        ui->tableWidget->setRowHeight(i,(ui->tableWidget->height()*0.9)/size);
        ui->tableWidget->setColumnWidth(i,(ui->tableWidget->width()*0.9)/size);
        for(int j=0;j<size;j++)
        {
            QTableWidgetItem *item=new QTableWidgetItem(QString("1"));
            ui->tableWidget->setItem(i,j,item);
        }
    }
}
