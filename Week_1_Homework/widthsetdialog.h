#ifndef WIDTHSETDIALOG_H
#define WIDTHSETDIALOG_H

#include <QDialog>

namespace Ui {
class WidthSetDialog;
}

class WidthSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WidthSetDialog(QWidget *parent = 0);
    ~WidthSetDialog();

private:
    Ui::WidthSetDialog *ui;

private slots:
    void GetWidth();

signals:
    void SendWidth(int);
};

#endif // WIDTHSETDIALOG_H
