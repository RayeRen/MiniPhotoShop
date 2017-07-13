#include "statecommonaction.h"
#include "../mainwindow.h"

int StateCommonAction::ActionTrigged(int state,Params params)
{
    vector<string> strings=params.getStrings();
    QString actionText=QString::fromStdString(strings[0]);
    MainWindow* pMainWindow=StateManager::GetpMainWindow();
    if(actionText==pMainWindow->ui->action_mergeLayout->text())
    {
        PerformLayoutMerge();
    }
    if(actionText==pMainWindow->ui->action_newCanvas->text())
    {
        Params params=NewCanvasDialog::GetCanvasSize(pMainWindow);
        if(params.getType()==RESULT::ACCEPTED)
        {
            pMainWindow->newCanvasCommand->setParams(params);
            pMainWindow->newCanvasCommand->exec();
        }
    }
    if(actionText==pMainWindow->ui->action_aboutQt->text())
    {
        QMessageBox::aboutQt(pMainWindow);
        return state;
    }
    if(actionText==pMainWindow->ui->action_drawLine->text())
    {
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
    if(actionText==pMainWindow->ui->action_newCanvas->text())
    {
        pMainWindow->newCanvasCommand->exec();
        return state;
    }
    if(actionText==pMainWindow->ui->action_saveCanvas->text())
    {
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
    if(actionText==pMainWindow->ui->action_saveAsPic->text())
    {
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
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                {
                    Params params;
                    params.setType(PIXMAP::INVERSECOLOR);
                    params.setInts({pMainWindow->ui->layoutListWidget->currentRow()});

                    pMainWindow->pixmapFilterCommand->setParams(params);
                    pMainWindow->pixmapFilterCommand->exec();
                }
            }
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
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                {
                    Params params;
                    params.setType(PIXMAP::HISTOEQUALIZING);
                    params.setInts({pMainWindow->ui->layoutListWidget->currentRow()});

                    pMainWindow->pixmapFilterCommand->setParams(params);
                    pMainWindow->pixmapFilterCommand->exec();
                }
            }
        }

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
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                {
                    Params params;
                    params.setType(PIXMAP::LOGOPERATION);
                    params.setInts({pMainWindow->ui->layoutListWidget->currentRow()});

                    pMainWindow->pixmapFilterCommand->setParams(params);
                    pMainWindow->pixmapFilterCommand->exec();
                }
            }
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_convo->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params newParams=ConvolutionDialog::GetConvolutionCore(pMainWindow);
            if(newParams.getType()==RESULT::ACCEPTED)
            {
                newParams.setType(PIXMAP::CONVOLUTION);
                vector<int> ints=newParams.getInts();
                ints.push_back(ints[0]);
                ints[0]=pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow());
                newParams.setInts(ints);
                pMainWindow->pixmapFilterCommand->setParams(newParams);
                pMainWindow->pixmapFilterCommand->exec();
            }
        }
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                Params newParams=ConvolutionDialog::GetConvolutionCore(pMainWindow);
                if(newParams.getType()==RESULT::ACCEPTED)
                {
                    newParams.setType(PIXMAP::CONVOLUTION);
                    vector<int> ints=newParams.getInts();
                    ints.push_back(ints[0]);
                    ints[0]=pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow());
                    newParams.setInts(ints);
                    pMainWindow->pixmapFilterCommand->setParams(newParams);
                    pMainWindow->pixmapFilterCommand->exec();
                }
            }
        }
        return state;
    }

    if(actionText==pMainWindow->ui->action_laplac->text())
    {
        if(pMainWindow->ifPixmap)
        {
            PerformLaplac();
        }
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                PerformLaplac();
            }
        }
        return state;
    }
    if(actionText==pMainWindow->ui->action_bilafilter->text())
    {
        if(pMainWindow->ifPixmap)
            PerformBilaFilter();
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                PerformBilaFilter();
            }
        }
        return state;
    }

    if(actionText==pMainWindow->ui->action_grey->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params newParams;
            newParams.setType(PIXMAP::CONVERTGREY);
            newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow())});

            pMainWindow->pixmapFilterCommand->setParams(newParams);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                Params newParams;
                newParams.setType(PIXMAP::CONVERTGREY);
                newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow())});

                pMainWindow->pixmapFilterCommand->setParams(newParams);
                pMainWindow->pixmapFilterCommand->exec();
            }
        }
        return state;
    }


    if(actionText==pMainWindow->ui->action_bin->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params newParams;
            newParams.setType(PIXMAP::CONVERTBIN);
            if(!QMessageBox::question(pMainWindow,QStringLiteral("图像二值化"),QStringLiteral("是否自动设定阈值？"),QStringLiteral("自动设定阈值"),
                                      QStringLiteral("手动输入阈值")))
                newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),-1});
            else
                newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),QInputDialog::getInt(pMainWindow,QStringLiteral("图像二值化"),
                                   QStringLiteral("请输入阈值"),150,1,255,1)});
            pMainWindow->pixmapFilterCommand->setParams(newParams);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                Params newParams;
                newParams.setType(PIXMAP::CONVERTGREY);
                if(!QMessageBox::question(pMainWindow,QStringLiteral("图像二值化"),QStringLiteral("是否自动设定阈值？"),QStringLiteral("自动设定阈值"),
                                          QStringLiteral("手动输入阈值")))
                    newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),-1});
                else
                    newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),QInputDialog::getInt(pMainWindow,QStringLiteral("图像二值化"),
                                       QStringLiteral("请输入阈值（取值范围0~255）"),150,0,255,1)});
                pMainWindow->pixmapFilterCommand->setParams(newParams);
                pMainWindow->pixmapFilterCommand->exec();
            }
        }
        return state;
    }

    if(actionText==pMainWindow->ui->action_lumaChange->text())
    {
        if(pMainWindow->ifPixmap)
        {
            Params newParams;
            newParams.setType(PIXMAP::LUMACHANGE);

            newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),QInputDialog::getInt(pMainWindow,QStringLiteral("图像亮度调整"),
                               QStringLiteral("请输入亮度变化量（取值范围-255~255）"),0,-255,255,1)});
            pMainWindow->pixmapFilterCommand->setParams(newParams);
            pMainWindow->pixmapFilterCommand->exec();
        }
        else
        {
            QMessageBox::critical(pMainWindow,QStringLiteral("错误 "),QStringLiteral("请选择一个位图图层以进行滤镜操作 "));
            if(!QMessageBox::question(pMainWindow,QStringLiteral("合并图层"),QStringLiteral("是否合并全部图层以进行滤镜操作？"),QStringLiteral("合并全部图层"),
                                      QStringLiteral("取消")))
            {
                PerformLayoutMerge();
                Params newParams;
                newParams.setType(PIXMAP::CONVERTGREY);
                newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),QInputDialog::getInt(pMainWindow,QStringLiteral("图像亮度调整"),
                                   QStringLiteral("请输入亮度变化量（取值范围-255~255）"),0,-255,255,1)});
                pMainWindow->pixmapFilterCommand->setParams(newParams);
                pMainWindow->pixmapFilterCommand->exec();
            }
        }
        return state;
    }


    return state;
}

void StateCommonAction::PerformLayoutMerge()
{
    MainWindow* pMainWindow=StateManager::GetpMainWindow();
    Params params;
    params.setInts({pMainWindow->ui->MainDisplayWidget->getCanvasWidth(),pMainWindow->ui->MainDisplayWidget->getCanvasHeight()});
    params.setStrings({string("tmp_file.png")});
    pMainWindow->saveAsPictureCommand->setParams(params);
    pMainWindow->saveAsPictureCommand->exec();
    pMainWindow->newCanvasCommand->setParams(params);
    pMainWindow->newCanvasCommand->exec();
    pMainWindow->addPicCommand->setParams(params);
    pMainWindow->addPicCommand->exec();
    {
        Params params;
        params.setInts({0});
        pMainWindow->changeSelectedCommand->setParams(params);
        pMainWindow->changeSelectedCommand->exec();
    }
}

void  StateCommonAction::PerformLaplac()
{
    MainWindow* pMainWindow=StateManager::GetpMainWindow();
    if(!QMessageBox::question(pMainWindow,QStringLiteral("拉普拉斯图像增强"),QStringLiteral("是否使用默认卷积核？"),
                              QStringLiteral("使用默认卷积核"),QStringLiteral("自定义卷积核")))
    {
        Params newParams;
        newParams.setType(PIXMAP::LAPLACIANENHANCE);
        newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),0});
        pMainWindow->pixmapFilterCommand->setParams(newParams);
        pMainWindow->pixmapFilterCommand->exec();
    }
    else
    {
        Params newParams=ConvolutionDialog::GetConvolutionCore(pMainWindow,PIXMAP::LAPLACIANENHANCE);
        if(newParams.getType()==RESULT::ACCEPTED)
        {
            newParams.setType(PIXMAP::LAPLACIANENHANCE);
            vector<int> ints=newParams.getInts();
            ints.push_back(ints[0]);
            ints[0]=pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow());
            newParams.setInts(ints);
            pMainWindow->pixmapFilterCommand->setParams(newParams);
            pMainWindow->pixmapFilterCommand->exec();
        }
    }
}

void StateCommonAction::PerformBilaFilter()
{
    Params newParams;
    MainWindow* pMainWindow=StateManager::GetpMainWindow();
    newParams.setType(PIXMAP::BILATERALFILTERING);
    if(!QMessageBox::question(pMainWindow,QStringLiteral("双边滤波"),QStringLiteral("是否使用默认参数？"),
                              QStringLiteral("使用默认参数"),QStringLiteral("自定义参数")))
    {
        newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),-1});
        newParams.setDoubles({-1.0,-1.0});
    }
    else
    {
        newParams.setInts({pMainWindow->ListMapIndex(pMainWindow->ui->layoutListWidget->currentRow()),
                           QInputDialog::getInt(pMainWindow,QStringLiteral("双边滤波"),QStringLiteral("请输入卷积核尺寸"),33,13,41,2)});
        newParams.setDoubles({QInputDialog::getDouble(pMainWindow,QStringLiteral("双边滤波"),
                              QStringLiteral("请输入空间域高斯函数标准差"),13.5,0.01,9999.0),QInputDialog::getDouble(pMainWindow,QStringLiteral("双边滤波"),
                              QStringLiteral("请输入值域高斯函数标准差"),0.15,0.01,9999.0)});
    }
    QMessageBox::information(pMainWindow,QStringLiteral("提示"),QStringLiteral("双边滤波耗时可能较长，计算期间窗口可能会无响应"));
    pMainWindow->pixmapFilterCommand->setParams(newParams);
    pMainWindow->pixmapFilterCommand->exec();
}
