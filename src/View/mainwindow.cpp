#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    state=STATE::INIT;
    pen=NULL;
    brush=NULL;
    displayImage=NULL;
    cursorX=-1;
    cursorY=-1;
    ui->setupUi(this);
    ui->MainDisplayWidget->SetState(&state);

    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this,SLOT(menuTriggered(QAction*)));

    ui->action_drawLine->setCheckable(true);
    ui->action_drawEllipse->setCheckable(true);
    ui->action_drawRect->setCheckable(true);
    ui->action_move->setCheckable(true);
    ui->action_scale->setCheckable(true);
    ui->action_rotate->setCheckable(true);
    connect(ui->penWidthSlider,SIGNAL(valueChanged(int)),this,SLOT(PenWidthSliderChanged(int)));
    connect(ui->MainDisplayWidget,SIGNAL(StateChanged()),this,SLOT(StateChanged()));
    connect(ui->foreColorButton,SIGNAL(pressed()),this,SLOT(ButtonForeColorPressed()));
    connect(ui->backColorButton,SIGNAL(pressed()),this,SLOT(ButtonBackColorPressed()));
    connect(ui->penStyleComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(PenStyleComboBoxChanged(int)));
    connect(ui->brushStyleComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(BrushStyleComboBoxChanged(int)));
    connect(ui->MainDisplayWidget,SIGNAL(CursorMove(int,int)),this,SLOT(UpdateCursorPosition(int,int)));
    ui->penStyleComboBox->insertItem(0,QString(QStringLiteral("无描边")),QString("no_pen"));
    ui->penStyleComboBox->insertItem(1,QString(QStringLiteral("实线")),QString("solid"));
    ui->penStyleComboBox->insertItem(2,QString(QStringLiteral("虚线")),QString("dash"));
    ui->penStyleComboBox->insertItem(3,QString(QStringLiteral("点线")),QString("dash_dot"));
    ui->penStyleComboBox->insertItem(4,QString(QStringLiteral("点划线")),QString("dash_dot_dot"));
    ui->penStyleComboBox->setCurrentIndex(1);

    ui->brushStyleComboBox->insertItem(0,QString(QStringLiteral("无填充")),QString("no_brush"));
    ui->brushStyleComboBox->insertItem(1,QString(QStringLiteral("纯色填充")),QString("solid"));
    ui->brushStyleComboBox->insertItem(2,QString(QStringLiteral("填充样式1")),QString("dense1"));
    ui->brushStyleComboBox->insertItem(3,QString(QStringLiteral("填充样式2")),QString("dense2"));
    ui->brushStyleComboBox->insertItem(4,QString(QStringLiteral("填充样式3")),QString("dense3"));
    ui->brushStyleComboBox->insertItem(5,QString(QStringLiteral("填充样式4")),QString("dense4"));
    ui->brushStyleComboBox->insertItem(6,QString(QStringLiteral("填充样式5")),QString("dense5"));
    ui->brushStyleComboBox->setCurrentIndex(1);
    //QListWidgetItem *item1=new QListWidgetItem(QIcon(":/img/img/SplashScreen.png"),QString("layout1"), ui->layoutListWidget);
    ui->layoutListWidget->setIconSize(QSize( SETTINGS::LIST_ICON_SIZE,SETTINGS::LIST_ICON_SIZE));
    //ui->layoutListWidget->insertItem(0,item1);
    connect(ui->layoutListWidget,SIGNAL(itemSelectionChanged()),this,SLOT(ListItemSelectionChanged()));
    ui->penWidthSlider->setToolTip(QString(QStringLiteral("设置线宽")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand)
{
    ui->MainDisplayWidget->setAddLineCommand(addLineCommand);
}
void MainWindow::setAddEllipseCommand(const shared_ptr<BaseCommand> &addEllipseCommand){
    ui->MainDisplayWidget->setAddEllipseCommand(addEllipseCommand);

}

void MainWindow::setAddRectCommand(const shared_ptr<BaseCommand> &addRectCommand)
{
    ui->MainDisplayWidget->setAddRectCommand(addRectCommand);
}

void MainWindow::setPenUpdateCommand(const shared_ptr<BaseCommand> &penUpdateCommand)
{
    this->penUpdateCommand=penUpdateCommand;
}

void MainWindow::update(Params params)
{
    switch(params.getType())
    {
    case NOTIFY::ADD_IMAGE_FAILED:
        QMessageBox::critical(this,QStringLiteral("错误"),QStringLiteral("打开图片失败"));
        break;
    case NOTIFY::NEW_LAYOUT:
    {
        vector<shared_ptr<void>> ptrs=params.getPtrs();
        shared_ptr<QImage> newImage=(static_pointer_cast<QImage>(ptrs[0]));
        QListWidgetItem *newItem=new QListWidgetItem(QIcon(QPixmap::fromImage(*newImage)),QStringLiteral("图层 %1").arg(ui->layoutListWidget->count()),ui->layoutListWidget);
        ui->layoutListWidget->insertItem(ui->layoutListWidget->count()-1,newItem);
    }
        break;
    case NOTIFY::DELETE_LAYOUT:{
        vector<int> ints=params.getInts();
        qDebug()<<"Go?"<<ints[0]<<ui->layoutListWidget->count();
        QListWidgetItem * deletedWidget=ui->layoutListWidget->takeItem(ints[0]);
        qDebug()<<"Remove:"<<ints[0];
        ui->layoutListWidget->removeItemWidget(deletedWidget);
        delete deletedWidget;
        qDebug()<<"After Delete Count"<<ui->layoutListWidget->count();

    }
        break;
    case NOTIFY::REFRESH_PREVIEW:
    {
        vector<int> ints=params.getInts();
        vector<shared_ptr<void>> ptrs=params.getPtrs();
        shared_ptr<QImage> newImage=(static_pointer_cast<QImage>(ptrs[0]));
        QListWidgetItem *item=ui->layoutListWidget->item(ints[0]);
        item->setIcon(QIcon(QPixmap::fromImage(*newImage)));
        qDebug()<<"item"<<ints[0];
    }
        break;
    case NOTIFY::DISPLAY_REFRESH:
        ui->MainDisplayWidget->paintUpdate();
        break;
    case NOTIFY::NO_LAYOUT_SELECTED:
        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("请在右侧图层列表选择需要操作的图层"));
        break;
    }
}

void MainWindow::SetPen(const Pen* pen)
{
    this->pen=pen;
    ui->foreColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(pen->getForeR()).arg(pen->getForeG()).arg(pen->getForeB()));
    ui->penWidthSlider->setValue(pen->getLineWidth());
    ui->MainDisplayWidget->SetPen(pen);
}

void MainWindow::SetBrush(const Brush* brush)
{
    this->brush=brush;
    ui->backColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(brush->getBackR()).arg(brush->getBackG()).arg(brush->getBackB()));
    ui->MainDisplayWidget->SetBrush(brush);
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

void MainWindow::menuTriggered(QAction* action)
{
    if(action->text()==ui->action_aboutQt->text())
    {
        QMessageBox::aboutQt(NULL);
        return;
    }
    if(action->text()==ui->action_drawLine->text())
    {

        state=STATE::DRAW_LINE_INIT;
        StateChanged();
        return;
    }
    if(action->text()==ui->action_drawEllipse->text())
    {

        state=STATE::DRAW_ELLIPSE_INIT;
        StateChanged();
        return;
    }
    if(action->text()==ui->action_drawRect->text())
    {

        state=STATE::DRAW_RECT_INIT;
        StateChanged();
        return;
    }
    if(action->text()==ui->action_openPic->text())
    {
        QFileDialog fileDialog(this);
        QString aimPicFileName=fileDialog.getOpenFileName(this,QStringLiteral("打开图片文件"),".","Images(*.png *.jpg *.bmp *.jpeg *.pbm *.gif *.pgm *.ppm *.xbm *.xpm)");
        if(!aimPicFileName.isNull())
        {
            Params params;
            params.setStrings({aimPicFileName.toStdString()});
            addPicCommand->setParams(params);
            addPicCommand->exec();
        }
        return;
    }
    if(action->text()==ui->action_newCanvas->text()){
        //New Project

    }
    if(action->text()==ui->action_saveCanvas->text()){
        //Save Project

    }
    if(action->text()==ui->action_saveAsPic->text()){
        //Save Picture
    }
    if(action->text()==ui->action_move->text())
    {
        state=STATE::MOVE_INIT;
        StateChanged();
        return;
    }
    if(action->text()==ui->action_scale->text())
    {
        state=STATE::SCALE_INIT;
        StateChanged();
    }

    if(action->text()==ui->action_rotate->text())
    {
        state=STATE::ROTATE_INIT;
        StateChanged();
    }
    if(action->text()==ui->action_aboutPro->text()){
        //temporal use to test undo redo

    }
    if(action->text()==ui->action_help->text()){
        //temporal use to test undo redo

    }
    if(action->text()==ui->action_undo->text())
    {
        Params params;
        undoCommand->setParams(params);
        undoCommand->exec();

    }
    if(action->text()==ui->action_redo->text())
    {
        Params params;
        redoCommand->setParams(params);
        redoCommand->exec();
    }
}

void MainWindow::StateChanged()
{
    ui->action_drawLine->setChecked(false);
    ui->action_drawEllipse->setChecked(false);
    ui->action_drawRect->setChecked(false);
    ui->action_move->setChecked(false);
    ui->action_scale->setChecked(false);
    ui->action_rotate->setChecked(false);
    switch(state)
    {
    case STATE::INIT:
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        break;
    case STATE::DRAW_LINE_INIT:
        ui->action_drawLine->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定直线的起点")));
        break;
    case STATE::DRAW_LINE:
        ui->action_drawLine->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
         UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定直线的终点")));
        break;
    case STATE::DRAW_ELLIPSE_INIT:
        ui->action_drawEllipse->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
         UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定椭圆的中心")));
        break;
    case STATE::DRAW_ELLIPSE:
        ui->action_drawEllipse->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
         UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定椭圆的长轴与短轴")));
        break;
    case STATE::DRAW_RECT_INIT:
        ui->action_drawRect->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定矩形的第一个顶点")));
        break;
    case STATE::DRAW_RECT:
        ui->action_drawRect->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        UpdateStatusBarInfo(QString(QStringLiteral("请松开鼠标以确定矩形的第二个顶点")));
        break;
    case STATE::MOVE_INIT:
        ui->MainDisplayWidget->setCursor(Qt::OpenHandCursor);
        ui->action_move->setChecked(true);
        UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始移动图层")));
        break;
    case STATE::MOVE:
        ui->MainDisplayWidget->setCursor(Qt::ClosedHandCursor);
        ui->action_move->setChecked(true);
UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下以移动图层")));
        break;

    case STATE::SCALE_INIT:
        ui->action_scale->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::SizeFDiagCursor);
        UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始缩放图层")));
        break;
case STATE::SCALE:
        ui->action_scale->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::SizeFDiagCursor);
      UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下以缩放图层")));
        break;
    case STATE::ROTATE_INIT:
        ui->action_rotate->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::SizeHorCursor);
UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始旋转图层")));
        break;
        case STATE::ROTATE:
        ui->action_rotate->setChecked(true);
        ui->MainDisplayWidget->setCursor(Qt::SizeHorCursor);
  UpdateStatusBarInfo(QString(QStringLiteral("请保持鼠标按下并水平移动鼠标以旋转图层")));
        break;
    }
    QWidget::update();
}

void MainWindow::ButtonForeColorPressed()
{
    const QColor& color = QColorDialog::getColor(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()),this,QStringLiteral("设置前景色"));
    if(color.isValid())
    {
        ui->foreColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        Params params;
        params.setType(COMMAND::UPDATE_PEN_COLOR);
        params.setInts({color.red(),color.green(),color.blue()});
        penUpdateCommand->setParams(params);
        penUpdateCommand->exec();
    }
}

void MainWindow::ButtonBackColorPressed()
{
    const QColor& color = QColorDialog::getColor(QColor(brush->getBackR(),brush->getBackG(),brush->getBackB()),this,QStringLiteral("设置背景色"));
    if(color.isValid())
    {
        ui->backColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        Params params;
        params.setType(COMMAND::UPDATE_BRUSH_COLOR);
        params.setInts({color.red(),color.green(),color.blue()});
        brushUpdateCommand->setParams(params);
        brushUpdateCommand->exec();
    }
}

void MainWindow::PenWidthSliderChanged(int value)
{
    if(penUpdateCommand!=nullptr)
    {
        Params params;
        params.setType(COMMAND::UPDATE_PEN_WIDTH);
        params.setInts({value});
        penUpdateCommand->setParams(params);
        penUpdateCommand->exec();
    }

}

void MainWindow::PenStyleComboBoxChanged(int index)
{
    if(penUpdateCommand!=nullptr)
    {
        Params params;
        params.setType(COMMAND::UPDATE_PEN_STYLE);
        params.setInts({index});
        penUpdateCommand->setParams(params);
        penUpdateCommand->exec();

    }
}

void MainWindow::BrushStyleComboBoxChanged(int index)
{
    if(brushUpdateCommand!=nullptr)
    {
        Params params;
        params.setType(COMMAND::UPDATE_BRUSH_STYLE);
        params.setInts({index});
        brushUpdateCommand->setParams(params);
        brushUpdateCommand->exec();

    }
}

void MainWindow::ListItemSelectionChanged()
{
    if(changeSelectedCommand!=nullptr)
    {
        Params params;
        params.setInts({ui->layoutListWidget->currentRow()});
        changeSelectedCommand->setParams(params);
        changeSelectedCommand->exec();
    }
}

void MainWindow::setLayoutTransCommand(const shared_ptr<BaseCommand> &layoutTransCommand)
{
    ui->MainDisplayWidget->setLayoutTransCommand(layoutTransCommand);
}

void MainWindow::UpdateCursorPosition(int x,int y)
{
    cursorX=x;
    cursorY=y;
    if(cursorX>=0&&cursorY>=0){
        QString messageA=QString(statusBarInfo)+QStringLiteral(" 位置")+QString("(%1,%2)").arg(cursorX).arg(cursorY);
        ui->statusBar->showMessage(messageA);
    }
     else
        ui->statusBar->showMessage(statusBarInfo);
}

void MainWindow::UpdateStatusBarInfo(QString info)
{
    statusBarInfo=info;
    if(cursorX>=0&&cursorY>=0){
        QString messageA=QString(statusBarInfo)+QStringLiteral(" 位置")+QString("(%1,%2)").arg(cursorX).arg(cursorY);
        ui->statusBar->showMessage(messageA);
    }else
        ui->statusBar->showMessage(statusBarInfo);
}
