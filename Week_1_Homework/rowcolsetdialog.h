#ifndef ROWCOLSETDIALOG_H
#define ROWCOLSETDIALOG_H

#include <QDialog>

namespace Ui {
class RowColSetDialog;
}

class RowColSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RowColSetDialog(QWidget *parent = 0);
    explicit RowColSetDialog(int, QWidget *parent = 0);
    ~RowColSetDialog();

private:
    Ui::RowColSetDialog *ui;

    void init();
    int RowCnt=5;

private slots:
    void GetRowCol();

signals:
    void SendRowCol(int);

};

#endif // ROWCOLSETDIALOG_H
