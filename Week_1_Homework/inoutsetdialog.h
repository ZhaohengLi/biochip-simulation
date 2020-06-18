#ifndef INOUTSETDIALOG_H
#define INOUTSETDIALOG_H

#include <QDialog>

namespace Ui {
class InOutSetDialog;
}

class InOutSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InOutSetDialog(int _RowCnt, QWidget *parent = 0);
    ~InOutSetDialog();

private:
    Ui::InOutSetDialog *ui;
    int RowCnt=5;
    int I1=2,I2=4,O1=1,O2=3,O3=5;

private slots:
    void GetInOut();

signals:
    void SendInOut(int,int,int,int,int);
};

#endif // INOUTSETDIALOG_H
