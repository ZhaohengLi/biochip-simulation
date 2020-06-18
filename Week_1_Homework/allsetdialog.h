#ifndef ALLSETDIALOG_H
#define ALLSETDIALOG_H

#include <QDialog>

namespace Ui {
class AllSetDialog;
}

class AllSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AllSetDialog(QWidget *parent = 0);
    ~AllSetDialog();

private:
    Ui::AllSetDialog *ui;

private slots:
    void GetAllSet();

signals:
    void SendAllSet(int,int,int,int,int,int);
};

#endif // ALLSETDIALOG_H
