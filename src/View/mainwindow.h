#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Common/Observer.h"
#include "../Common/BaseCommand.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public Observer {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void setAddLineCommand(const shared_ptr<BaseCommand> &addLineCommand);

    virtual void update(Params params);

private:
    Ui::MainWindow *ui;
    shared_ptr<BaseCommand> addLineCommand;
};

#endif // MAINWINDOW_H
