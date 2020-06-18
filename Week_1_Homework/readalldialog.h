#ifndef READALLDIALOG_H
#define READALLDIALOG_H

#include <QDialog>

namespace Ui {
class ReadAllDialog;
}

class ReadAllDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadAllDialog(QWidget *parent = 0);
    ~ReadAllDialog();

private:
    Ui::ReadAllDialog *ui;
};

#endif // READALLDIALOG_H
