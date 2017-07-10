#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Constants.h"
#include "../Common/DataStructure.h"
#include <QMainWindow>
#include "../Common/Observer.h"
#include "../Common/BaseCommand.h"
#include "../View/imagewidget.h"

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

    void setBrushUpdateCommand(const shared_ptr<BaseCommand> &brushUpdateCommand){this->brushUpdateCommand=brushUpdateCommand;}
    void setChangeSelectedCommand(const shared_ptr<BaseCommand> &changeSelectedCommand){this->changeSelectedCommand=changeSelectedCommand;}
    void setLoadProjectCommand(const shared_ptr<BaseCommand> &loadProjectCommand){this->loadProjectCommand=loadProjectCommand;}
    void setNewProjectCommand(const shared_ptr<BaseCommand> &newProjectCommand){this->newProjectCommand=newProjectCommand;}
    void setSaveProjectCommand(const shared_ptr<BaseCommand> &saveProjectCommand){this->saveProjectCommand=saveProjectCommand;}
    void setUndoCommand(const shared_ptr<BaseCommand> &undoCommand){this->undoCommand=undoCommand;}
    void setRedoCommand(const shared_ptr<BaseCommand> &redoCommand){this->redoCommand=redoCommand;}

    void SetPen(const Pen* pen);
    void SetBrush(const Brush* brush);
    void SetDisplayImage(const QImage* displayImage);
    virtual void update(Params params);

private:
    Ui::MainWindow *ui;
    const Pen* pen;
    const Brush* brush;
    const QImage* displayImage;
    QString statusBarInfo;
    int cursorX,cursorY;
    int state;
     shared_ptr<BaseCommand> newCanvasCommand,
     penUpdateCommand,brushUpdateCommand,addPicCommand,changeSelectedCommand,
     loadProjectCommand,saveProjectCommand,newProjectCommand,undoCommand,redoCommand,layoutTransNotifyCommand;
QMenu* canvasPopMenu;
 public slots:
     void menuTriggered(QAction*);   //响应菜单栏事件
     void StateChanged();
     void ButtonForeColorPressed();
     void ButtonBackColorPressed();
     void PenWidthSliderChanged(int);
     void PenStyleComboBoxChanged(int);
     void BrushStyleComboBoxChanged(int);
     void ListItemSelectionChanged();
     void UpdateCursorPosition(int,int);
     void UpdateStatusBarInfo(QString);
     void CanvasPopMenuShow(const QPoint);
};

#endif // MAINWINDOW_H
