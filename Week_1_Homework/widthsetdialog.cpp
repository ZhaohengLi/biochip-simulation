#include "widthsetdialog.h"
#include "ui_widthsetdialog.h"
#include <QMessageBox>
WidthSetDialog::WidthSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WidthSetDialog)
{
    ui->setupUi(this);
    connect(ui->YesBtn,SIGNAL(clicked(bool)),this,SLOT(GetWidth()));
    connect(ui->NoBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    ui->YesBtn->setDefault(true);
    setWindowTitle("设置管道宽度");

}

WidthSetDialog::~WidthSetDialog()
{
    delete ui;
}

void WidthSetDialog::GetWidth(){
    if(ui->WidthInputSpinBox->value()<20){
        QMessageBox::critical(this,"输入不合法","请正确输入数据:\n管道宽度最小为20单位");
    } else {
        emit SendWidth(ui->WidthInputSpinBox->value());
        this->close();
    }
}
