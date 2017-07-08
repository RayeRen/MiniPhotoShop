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
    void SetPen(const Pen* pen);
    void SetBrush(const Brush* brush);
    void SetDisplayImage(const QImage* displayImage);
    virtual void update(Params params);

private:
    Ui::MainWindow *ui;
    const Pen* pen;
    const Brush* brush;
    const QImage* displayImage;
    int state;
};

#endif // MAINWINDOW_H
