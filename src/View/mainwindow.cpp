#include "mainwindow.h"

static QWizardPage *createPage1()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("简介"));
    QLabel *label = new QLabel(QStringLiteral("此向导将介绍如何使用Mini PhotoShop"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage2()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("窗口布局"));
    QLabel *label = new QLabel(QStringLiteral("窗口中心为画布\n窗口右侧为图层列表\n窗口上方为菜单栏与快捷工具栏\n快捷工具栏下方为描边与填充设置区，从左至右依次为：描边颜色设置、描边宽度设置、描边线型设置、填充颜色设置、填充方式设置\n窗口下方为状态栏"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage3()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("基本操作"));
    QLabel *label = new QLabel(QStringLiteral("将鼠标移至画布并滚动鼠标滚轮可以缩放画布，在画布以及图层列表上单击鼠标右键可以显示弹出式菜单。\n单击快捷工具栏或菜单栏可以切换工具或执行操作，图层列表上方三个按键的功能分别为上移当前图层、下移当前图层与删除当前图层\n每次绘制都会自动生成一个新图层，图层分为 线段、矩形、椭圆与位图四种"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage4()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("工具说明"));
    QLabel *label = new QLabel(QStringLiteral("画直线：在新图层上通过两点绘制一条直线\n"
                                              "画椭圆：在新图层上通过确定椭圆中心与长短半轴绘制一个椭圆\n"
                                              "画矩形：在新图层上通过确定矩形两个对角线顶点绘制一个矩形\n"
                                              "平移：对所选图层通过拖动鼠标进行移动\n"
                                              "旋转：对所选图层通过水平移动鼠标进行旋转\n"
                                              "缩放：对所选图层通过拖动鼠标进行缩放"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage5()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("操作说明"));
    QLabel *label = new QLabel(QStringLiteral("新建工程：清空当前工程，输入画布并尺寸新建工程\n"
                                              "打开工程：打开.mps工程文件\n"
                                              "打开图片：将外部图片插入至新图层\n"
                                              "保存工程：保存当前工程\n"
                                              "另存为图片：将当前工程输出至图片"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage6()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("撤销与重做"));
    QLabel *label = new QLabel(QStringLiteral("通过撤销与重做命令，可以撤销修改或恢复被撤销的修改"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

static QWizardPage *createPage7()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("图层操作"));
    QLabel *label = new QLabel(QStringLiteral("可以对当前选定的图层进行上移、下移与删除操作\n可以将当前所有图层合并为一个位图图层"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}
static QWizardPage *createPage8()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(QStringLiteral("滤镜操作"));
    QLabel *label = new QLabel(QStringLiteral("滤镜只能对于位图图层操作\n如果需要对非位图图层进行滤镜操作，需要首先将所有图层合并为位图图层"));
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pen=NULL;
    brush=NULL;
    displayImage=NULL;
    cursorX=-1;
    cursorY=-1;
    ifPixmap=0;
    ui->setupUi(this);
    wizard=new QWizard;
    wizard->setWindowTitle(QStringLiteral("向导"));
    wizard->addPage(createPage1());
    wizard->addPage(createPage2());
    wizard->addPage(createPage3());
    wizard->addPage(createPage4());
    wizard->addPage(createPage5());
    wizard->addPage(createPage6());
    wizard->addPage(createPage7());
    wizard->addPage(createPage8());
    wizard->setWizardStyle(QWizard::AeroStyle);
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
    ui->brushStyleComboBox->insertItem(7,QString(QStringLiteral("填充样式6")),QString("dense6"));
    ui->brushStyleComboBox->insertItem(8,QString(QStringLiteral("填充样式7")),QString("dense7"));
    ui->brushStyleComboBox->insertItem(9,QString(QStringLiteral("水平线填充")),QString("hor"));
    ui->brushStyleComboBox->insertItem(10,QString(QStringLiteral("竖直线填充")),QString("ver"));
    ui->brushStyleComboBox->insertItem(11,QString(QStringLiteral("网格线填充")),QString("cross"));
    ui->brushStyleComboBox->insertItem(12,QString(QStringLiteral("左斜线填充")),QString("bdiag"));
    ui->brushStyleComboBox->insertItem(13,QString(QStringLiteral("右斜线填充")),QString("fdiag"));
    ui->brushStyleComboBox->insertItem(14,QString(QStringLiteral("斜网格线填充")),QString("diagcross"));

    ui->brushStyleComboBox->setCurrentIndex(1);
    //QListWidgetItem *item1=new QListWidgetItem(QIcon(":/img/img/SplashScreen.png"),QString("layout1"), ui->layoutListWidget);
    ui->layoutListWidget->setIconSize(QSize( SETTINGS::LIST_ICON_SIZE,SETTINGS::LIST_ICON_SIZE));
    //ui->layoutListWidget->insertItem(0,item1);
    connect(ui->layoutListWidget,SIGNAL(itemSelectionChanged()),this,SLOT(ListItemSelectionChanged()));
    //ui->layoutListWidget->setSortingEnabled(true);

    ui->penWidthSlider->setToolTip(QString(QStringLiteral("设置线宽")));
    ui->MainDisplayWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->layoutListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->MainDisplayWidget,SIGNAL(customContextMenuRequested(const QPoint)),this,SLOT(CanvasPopMenuShow(const QPoint)));
    connect(ui->layoutListWidget,SIGNAL(customContextMenuRequested(const QPoint)),this,SLOT(ListPopMenuShow(const QPoint)));
    canvasPopMenu=new QMenu(ui->MainDisplayWidget);
    canvasPopMenu->addAction(ui->action_drawLine);
    canvasPopMenu->addAction(ui->action_drawRect);
    canvasPopMenu->addAction(ui->action_drawEllipse);
    canvasPopMenu->addAction(ui->action_move);
    canvasPopMenu->addAction(ui->action_scale);
    canvasPopMenu->addAction(ui->action_rotate);
    canvasPopMenu->addAction(ui->action_undo);
    canvasPopMenu->addAction(ui->action_redo);
    listPopMenu=new QMenu(ui->layoutListWidget);
    listPopMenu->addAction(ui->action_layoutUp);
    listPopMenu->addAction(ui->action_layoutDown);
    listPopMenu->addAction(ui->action_deleteLayout);

    connect(ui->layoutUpToolButton,SIGNAL(pressed()),ui->action_layoutUp,SLOT(trigger()));
    connect(ui->layoutDownToolButton,SIGNAL(pressed()),ui->action_layoutDown,SLOT(trigger()));
    connect(ui->layoutDeleteToolButton,SIGNAL(pressed()),ui->action_deleteLayout,SLOT(trigger()));
    connect(ui->MainDisplayWidget,SIGNAL(NewCanvasScale(double)),this,SLOT(CanvasScaleChanged(double)));
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
void MainWindow::ConnectQListWidget()
{
    connect(ui->layoutListWidget,SIGNAL(itemSelectionChanged()),this,SLOT(ListItemSelectionChanged()));
}
void MainWindow::DisConnentQListWidget()
{
    disconnect(ui->layoutListWidget,SIGNAL(itemSelectionChanged()),this,SLOT(ListItemSelectionChanged()));
}

void MainWindow::update(Params params)
{
    DisConnentQListWidget();
    switch(params.getType())
    {
    case NOTIFY::ADD_IMAGE_FAILED:
        QMessageBox::critical(this,QStringLiteral("错误"),QStringLiteral("打开图片失败"));
        break;
    case NOTIFY::NEW_LAYOUT:
    {
        vector<shared_ptr<void>> ptrs=params.getPtrs();
        vector<int> ints=params.getInts();
        vector<string> strings=params.getStrings();
        shared_ptr<QImage> newImage=(static_pointer_cast<QImage>(ptrs[0]));
        QListWidgetItem *newItem=new QListWidgetItem(QIcon(QPixmap::fromImage(*newImage)),QString::fromStdString(strings[0]));
        //ui->layoutListWidget->insertItem(IndexMapList(ints[0]),newItem);
        ui->layoutListWidget->insertItem(IndexMapList(ints[0])+1,newItem);
    }
        break;
    case NOTIFY::DELETE_LAYOUT:{
        vector<int> ints=params.getInts();
        ui->layoutListWidget->setCurrentRow(IndexMapList(ints[1]));
        QListWidgetItem * deletedWidget=ui->layoutListWidget->takeItem(IndexMapList(ints[0]));
        ui->layoutListWidget->removeItemWidget(deletedWidget);
        delete deletedWidget;
    }
        break;
    case NOTIFY::REFRESH_PREVIEW:
    {
        vector<int> ints=params.getInts();
        vector<shared_ptr<void>> ptrs=params.getPtrs();
        shared_ptr<QImage> newImage=(static_pointer_cast<QImage>(ptrs[0]));
        QListWidgetItem *item=ui->layoutListWidget->item(IndexMapList(ints[0]));
        item->setIcon(QIcon(QPixmap::fromImage(*newImage)));
    }
        break;
    case NOTIFY::REFRESH_SELECTED_STATE:
    {
        vector<int> ints=params.getInts();
        if(ui->layoutListWidget->currentRow()!=IndexMapList(ints[0]))ui->layoutListWidget->setCurrentRow(IndexMapList(ints[0]));

    }
        break;
    case NOTIFY::DISPLAY_REFRESH:
        ui->MainDisplayWidget->paintUpdate();
        break;
    case NOTIFY::NO_LAYOUT_SELECTED:
        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("请在右侧图层列表选择需要操作的图层"));
        break;
    case NOTIFY::CLEAR:
        ui->MainDisplayWidget->update();
        ui->layoutListWidget->clear();

        break;
    case NOTIFY::IF_LAYOUT_PIXMAP:
    {
        vector<int> ints=params.getInts();
        ifPixmap=ints[0];
    }
        break;

    }
    ConnectQListWidget();
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
    params.setInts({(int)SETTINGS::canvasWidth,(int)SETTINGS::canvasHeight});
    newCanvasCommand->setParams(params);
    newCanvasCommand->exec();
}

void MainWindow::menuTriggered(QAction* action)
{
    Params params;
    params.setStrings({(action->text()).toStdString()});
    StateManager::Run(EVENT::ACTION_TRIGGERED,params);
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
        params.setInts({ListMapIndex(ui->layoutListWidget->currentRow())});
        changeSelectedCommand->setParams(params);
        changeSelectedCommand->exec();
    }
}

void MainWindow::setLayoutTransCommand(const shared_ptr<BaseCommand> &layoutTransCommand)
{
    ui->MainDisplayWidget->setLayoutTransCommand(layoutTransCommand);
}
void MainWindow::setLayoutTransNotifyCommand(const shared_ptr<BaseCommand> &layoutTransNotifyCommand)
{
    ui->MainDisplayWidget->setLayoutTransNotifyCommand(layoutTransNotifyCommand);
}

void MainWindow::UpdateCursorPosition(int x,int y)
{
    cursorX=x;
    cursorY=y;
    if(cursorX>=0&&cursorY>=0)
    {
        QString messageA=QString(statusBarInfo)+QStringLiteral(" 位置")+QString("(%1,%2)").arg(cursorX).arg(cursorY);
        ui->statusBar->showMessage(messageA);
    }
    else
        ui->statusBar->showMessage(statusBarInfo);
}

void MainWindow::UpdateStatusBarInfo(QString info)
{
    statusBarInfo=info;
    if(cursorX>=0&&cursorY>=0)
    {
        QString messageA=QString(statusBarInfo)+QStringLiteral(" 位置")+QString("(%1,%2)").arg(cursorX).arg(cursorY);
        ui->statusBar->showMessage(messageA);
    }
    else
        ui->statusBar->showMessage(statusBarInfo);
}

void MainWindow::CanvasPopMenuShow(const QPoint)
{
    canvasPopMenu->exec(QCursor::pos());
}

void MainWindow::ListPopMenuShow(const QPoint)
{
    listPopMenu->exec(QCursor::pos());
}

void MainWindow::CanvasScaleChanged(double newScale)
{
    ui->scaleLabel->setText(QStringLiteral("缩放 ")+QString("%1 %").arg(newScale*100));
}

void MainWindow::ShowHelp()
{
    wizard->show();
}
