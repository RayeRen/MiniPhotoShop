#include "statecommonaction.h"
#include "../mainwindow.h"
int StateCommonAction::ActionTrigged(int state,Params params)
{
    vector<string> strings=params.getStrings();
    QString actionText=QString::fromStdString(strings[0]);
    MainWindow* pMainWindow=StateManager::GetpMainWindow();

    if(actionText==pMainWindow->ui->action_aboutQt->text())
    {
        QMessageBox::aboutQt(NULL);
        return state;
    }
    if(actionText==pMainWindow->ui->action_drawLine->text())
    {
        //DELETE_BEGIN
        pMainWindow->state=STATE::DRAW_LINE_INIT;
        pMainWindow->StateChanged();
        //DELETE_END

        pMainWindow->ui->action_drawEllipse->setChecked(false);
        pMainWindow->ui->action_drawRect->setChecked(false);
        pMainWindow->ui->action_move->setChecked(false);
        pMainWindow->ui->action_scale->setChecked(false);
        pMainWindow->ui->action_rotate->setChecked(false);

        pMainWindow->ui->action_drawLine->setChecked(true);
        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定直线的起点 ")));
        return STATE::DRAW_LINE_INIT;
    }
    if(actionText==pMainWindow->ui->action_drawEllipse->text())
    {
        //DELETE_BEGIN
        pMainWindow->state=STATE::DRAW_ELLIPSE_INIT;
        pMainWindow->StateChanged();
        //DELETE_END

        pMainWindow->ui->action_drawLine->setChecked(false);
        pMainWindow->ui->action_drawRect->setChecked(false);
        pMainWindow->ui->action_move->setChecked(false);
        pMainWindow->ui->action_scale->setChecked(false);
        pMainWindow->ui->action_rotate->setChecked(false);


        pMainWindow->ui->action_drawEllipse->setChecked(true);
        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定椭圆的中心 ")));
        return STATE::DRAW_ELLIPSE_INIT;
    }
    if(actionText==pMainWindow->ui->action_drawRect->text())
    {
        //DELETE_BEGIN
        pMainWindow->state=STATE::DRAW_RECT_INIT;
        pMainWindow->StateChanged();
        //DELETE_END

        pMainWindow->ui->action_drawLine->setChecked(false);
        pMainWindow->ui->action_drawEllipse->setChecked(false);
        pMainWindow->ui->action_move->setChecked(false);
        pMainWindow->ui->action_scale->setChecked(false);
        pMainWindow->ui->action_rotate->setChecked(false);

        pMainWindow->ui->action_drawRect->setChecked(true);
        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::CrossCursor);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标以确定矩形的第一个顶点 ")));

        return STATE::DRAW_RECT_INIT;
    }
    if(actionText==pMainWindow->ui->action_openPic->text())
    {
        QFileDialog fileDialog(pMainWindow);
        QString aimPicFileName=fileDialog.getOpenFileName(pMainWindow,QStringLiteral("打开图片文件"),".","Images(*.png *.jpg *.bmp *.jpeg *.pbm *.gif *.pgm *.ppm *.xbm *.xpm)");
        if(!aimPicFileName.isNull())
        {
            Params params;
            params.setStrings({aimPicFileName.toStdString()});
            pMainWindow->addPicCommand->setParams(params);
            pMainWindow->addPicCommand->exec();
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_newCanvas->text()){
        //New Project
        pMainWindow->newProjectCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_saveCanvas->text()){
        //Save Project
        QFileDialog fileDialog(pMainWindow);
        QString aimProjectFileName=fileDialog.getSaveFileName(pMainWindow,QStringLiteral("保存项目文件"),".","MiniPhotoshop Project(*.mps)");
        if(!aimProjectFileName.isNull())
        {
            Params params;
            params.setStrings({aimProjectFileName.toStdString()});
            pMainWindow->saveProjectCommand->setParams(params);
            pMainWindow->saveProjectCommand->exec();
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_saveAsPic->text()){
        //Save Picture
        QFileDialog fileDialog(pMainWindow);
        QString aimPicFileName=fileDialog.getSaveFileName(pMainWindow,QStringLiteral("保存图片文件"),".","Images(*.png *.jpg *.bmp *.jpeg *.pbm *.gif *.pgm *.ppm *.xbm *.xpm)");
        if(!aimPicFileName.isNull())
        {
            Params params;
            params.setStrings({aimPicFileName.toStdString()});
            pMainWindow->saveAsPictureCommand->setParams(params);
            pMainWindow->saveAsPictureCommand->exec();
        }
        return state;
    }

    if(actionText==pMainWindow->ui->action_move->text())
    {
         //DELETE_BEGIN
        pMainWindow->state=STATE::MOVE_INIT;
        pMainWindow->StateChanged();
         //DELETE_END

        pMainWindow->ui->action_drawLine->setChecked(false);
        pMainWindow->ui->action_drawEllipse->setChecked(false);
        pMainWindow->ui->action_drawRect->setChecked(false);
        pMainWindow->ui->action_scale->setChecked(false);
        pMainWindow->ui->action_rotate->setChecked(false);

        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::OpenHandCursor);
        pMainWindow->ui->action_move->setChecked(true);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始移动图层 ")));

        return STATE::MOVE_INIT;
    }
    if(actionText==pMainWindow->ui->action_scale->text())
    {
         //DELETE_BEGIN
        pMainWindow->state=STATE::SCALE_INIT;
        pMainWindow->StateChanged();
         //DELETE_END

        pMainWindow->ui->action_drawLine->setChecked(false);
        pMainWindow->ui->action_drawEllipse->setChecked(false);
        pMainWindow->ui->action_drawRect->setChecked(false);
        pMainWindow->ui->action_move->setChecked(false);
        pMainWindow->ui->action_rotate->setChecked(false);

        pMainWindow->ui->action_scale->setChecked(true);
        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::SizeFDiagCursor);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始缩放图层 ")));

        return STATE::SCALE_INIT;
    }

    if(actionText==pMainWindow->ui->action_rotate->text())
    {
         //DELETE_BEGIN
        pMainWindow->state=STATE::ROTATE_INIT;
        pMainWindow->StateChanged();
         //DELETE_END

        pMainWindow->ui->action_drawLine->setChecked(false);
        pMainWindow->ui->action_drawEllipse->setChecked(false);
        pMainWindow->ui->action_drawRect->setChecked(false);
        pMainWindow->ui->action_move->setChecked(false);
        pMainWindow->ui->action_scale->setChecked(false);

        pMainWindow->ui->MainDisplayWidget->setCursor(Qt::SizeHorCursor);
        pMainWindow->UpdateStatusBarInfo(QString(QStringLiteral("请按下鼠标开始旋转图层 ")));

        return STATE::ROTATE_INIT;
    }
    if(actionText==pMainWindow->ui->action_aboutPro->text())
    {
        QMessageBox::about(NULL,QStringLiteral("关于"),"Mini PhotoShop\nPowered By Qt5");
        return state;
    }
    if(actionText==pMainWindow->ui->action_help->text())
    {
        return state;
    }
    if(actionText==pMainWindow->ui->action_undo->text())
    {
        Params params;
        pMainWindow->undoCommand->setParams(params);
        pMainWindow->undoCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_redo->text())
    {
        Params params;
        pMainWindow->redoCommand->setParams(params);
        pMainWindow->redoCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_openPro->text())
    {
        //打开工程
        QFileDialog fileDialog(pMainWindow);
        QString aimProjectFileName=fileDialog.getOpenFileName(pMainWindow,QStringLiteral("打开项目文件"),".","MiniPhotoshop Project(*.mps)");
        if(!aimProjectFileName.isNull())
        {
            Params params;
            params.setStrings({aimProjectFileName.toStdString()});
            pMainWindow->loadProjectCommand->setParams(params);
            pMainWindow->loadProjectCommand->exec();
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_deleteLayout->text())
    {
        //删除图层
        pMainWindow->deleteLayoutCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_layoutUp->text())
    {
        Params params;
        params.setType(COMMAND::LAYOUT_ORDER_UP);
        pMainWindow->layoutOrderChangeCommand->setParams(params);
        pMainWindow->layoutOrderChangeCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_layoutDown->text())
    {
        Params params;
        params.setType(COMMAND::LAYOUT_ORDER_DOWN);
        pMainWindow->layoutOrderChangeCommand->setParams(params);
        pMainWindow->layoutOrderChangeCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_inverse->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params params;
            params.setType(PIXMAP::INVERSECOLOR);
            params.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow())});

            pMainWindow->pixmapFilterCommand->setParams(params);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else{

            QString title=QStringLiteral("错误 ");
            qDebug()<<title;
             QMessageBox::critical(pMainWindow,title,QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_histoEqu->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params params;
            params.setType(PIXMAP::HISTOEQUALIZING);
            params.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow())});

            pMainWindow->pixmapFilterCommand->setParams(params);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else
             QMessageBox::critical(pMainWindow,QStringLiteral("错误"),QStringLiteral("请选择一个位图图层以进行滤镜操作"));

        return state;
    }
    if(actionText==pMainWindow->ui->action_logOper->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params params;
            params.setType(PIXMAP::LOGOPERATION);
            params.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow())});

            pMainWindow->pixmapFilterCommand->setParams(params);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else
             QMessageBox::critical(pMainWindow,QStringLiteral("错误"),QStringLiteral("请选择一个位图图层以进行滤镜操作"));

        return state;
    }
    return state;
}
