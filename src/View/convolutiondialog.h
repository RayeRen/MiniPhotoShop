#ifndef CONVOLUTIONDIALOG_H
#define CONVOLUTIONDIALOG_H

#include <QDialog>
#include "../Common/Params.h"
#include "../Constants.h"
namespace Ui {
class ConvolutionDialog;
}

class ConvolutionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConvolutionDialog(QWidget *parent = 0,int defaultValue=PIXMAP::INVERSECOLOR);
    ~ConvolutionDialog();
    static Params GetConvolutionCore(QWidget *parent=0,int defaultValue=PIXMAP::INVERSECOLOR);
private:
    Ui::ConvolutionDialog *ui;
    static Params params;
public slots:
    void AcceptButtonPressed();
    void RejectButtonPressed();
    void SizeChanged(int);
};

#endif // CONVOLUTIONDIALOG_H
