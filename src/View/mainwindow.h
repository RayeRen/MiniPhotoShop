#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../Constants.h"
#include "../Common/DataStructure.h"
#include <QMainWindow>
#include "../Common/Observer.h"
#include "../Common/BaseCommand.h"
#include "imagewidget.h"
#include "statemanager.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QWizard>
#include "ui_mainwindow.h"
#include "newcanvasdialog.h"
#include "convolutiondialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public Observer {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand);
    void setAddPicCommand(const shared_ptr<BaseCommand> &addPicCommand){this->addPicCommand=addPicCommand;}
    void setAddEllipseCommand(const shared_ptr<BaseCommand> &addEllipseCommand);
    void setAddRectCommand(const shared_ptr<BaseCommand> &addRectCommand);
    void setNewCanvasCommand(const shared_ptr<BaseCommand> &newCanvasCommand);
    void setPenUpdateCommand(const shared_ptr<BaseCommand> &penUpdateCommand);
    void setLayoutTransCommand(const shared_ptr<BaseCommand> &layoutTransCommand);
    void setLayoutTransNotifyCommand(const shared_ptr<BaseCommand> &layoutTransNotifyCommand);
    void setPixmapFilterCommand(const shared_ptr<BaseCommand> &pixmapFilterCommand){this->pixmapFilterCommand=pixmapFilterCommand;}

    void setBrushUpdateCommand(const shared_ptr<BaseCommand> &brushUpdateCommand){this->brushUpdateCommand=brushUpdateCommand;}
    void setChangeSelectedCommand(const shared_ptr<BaseCommand> &changeSelectedCommand){this->changeSelectedCommand=changeSelectedCommand;}
    void setLoadProjectCommand(const shared_ptr<BaseCommand> &loadProjectCommand){this->loadProjectCommand=loadProjectCommand;}
    void setNewProjectCommand(const shared_ptr<BaseCommand> &newProjectCommand){this->newProjectCommand=newProjectCommand;}
    void setSaveProjectCommand(const shared_ptr<BaseCommand> &saveProjectCommand){this->saveProjectCommand=saveProjectCommand;}
    void setUndoCommand(const shared_ptr<BaseCommand> &undoCommand){this->undoCommand=undoCommand;}
    void setRedoCommand(const shared_ptr<BaseCommand> &redoCommand){this->redoCommand=redoCommand;}
    void setDeleteLayoutCommand(const shared_ptr<BaseCommand> &deleteLayoutCommand){this->deleteLayoutCommand=deleteLayoutCommand;}
    void setSaveAsPictureCommand(const shared_ptr<BaseCommand> &saveAsPictureCommand){this->saveAsPictureCommand=saveAsPictureCommand;}
    void setLayoutOrderChangeCommand(const shared_ptr<BaseCommand> &layoutOrderChangeCommand){this->layoutOrderChangeCommand=layoutOrderChangeCommand;}
    void SetPen(const Pen* pen);
    void SetBrush(const Brush* brush);
    void SetDisplayImage(const QImage* displayImage);
    void ShowHelp();
    virtual void update(Params params);

    void ConnectQListWidget();
    void DisConnentQListWidget();
    int  ListMapIndex(int listindex){
        //表的Index转化为内部数据的Index
        int after=listindex;
        if(listindex>=0)after=ui->layoutListWidget->count()-1-listindex;
        qDebug()<<"ListMapIndex:Before:"<<listindex<<"after:"<<after;
        return after;
    }
    int IndexMapList(int index){
        //内部数据的Index转化为表的Index
        int after=index;
        if(index>=0)after=ui->layoutListWidget->count()-1-index;
        qDebug()<<"IndexMapList:Before:"<<index<<"after:"<<after;
        return after;
    }


    friend class BaseState;
    friend class DrawLineInitState;
    friend class DrawLineState;
    friend class DrawEllipseInitState;
    friend class DrawEllipseState;
    friend class DrawRectInitState;
    friend class DrawRectState;
    friend class MoveInitState;
    friend class MoveState;
    friend class ScaleInitState;
    friend class ScaleState;
    friend class RotateInitState;
    friend class RotateState;
    friend class StateCommonAction;

private:
    Ui::MainWindow *ui;
    const Pen* pen;
    const Brush* brush;
    const QImage* displayImage;
    QString statusBarInfo;
    int cursorX,cursorY;
    int ifPixmap,selectedLayout;
     shared_ptr<BaseCommand> newCanvasCommand,
     penUpdateCommand,brushUpdateCommand,addPicCommand,changeSelectedCommand,
     loadProjectCommand,saveProjectCommand,newProjectCommand,undoCommand,redoCommand,
     pixmapFilterCommand,layoutTransNotifyCommand,deleteLayoutCommand,saveAsPictureCommand,layoutOrderChangeCommand;
    QMenu* canvasPopMenu,*listPopMenu;
    QWizard* wizard;
 public slots:
     void menuTriggered(QAction*);   //响应菜单栏事件
     void ButtonForeColorPressed();
     void ButtonBackColorPressed();
     void PenWidthSliderChanged(int);
     void PenStyleComboBoxChanged(int);
     void BrushStyleComboBoxChanged(int);
     void ListItemSelectionChanged();
     void UpdateCursorPosition(int,int);
     void UpdateStatusBarInfo(QString);
     void CanvasPopMenuShow(const QPoint);
     void ListPopMenuShow(const QPoint);
     void CanvasScaleChanged(double);
};

#endif // MAINWINDOW_H
