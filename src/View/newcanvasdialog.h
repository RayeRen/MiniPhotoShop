#ifndef NEWCANVASDIALOG_H
#define NEWCANVASDIALOG_H
#include "../Constants.h"
#include "../Common/Params.h"
#include <QDialog>

namespace Ui {
class NewCanvasDialog;
}

class NewCanvasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCanvasDialog(QWidget *parent = 0);
    ~NewCanvasDialog();
static Params GetCanvasSize(QWidget *parent = 0);

private:
    Ui::NewCanvasDialog *ui;
    static Params params;
  public slots:
    void AcceptButton();
    void RejectButton();
};

#endif // NEWCANVASDIALOG_H
