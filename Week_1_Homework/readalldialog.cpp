#include "readalldialog.h"
#include "ui_readalldialog.h"

ReadAllDialog::ReadAllDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadAllDialog)
{
    ui->setupUi(this);
    setWindowTitle("全部流速结果");
}

ReadAllDialog::~ReadAllDialog()
{
    delete ui;
}
