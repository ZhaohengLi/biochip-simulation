#include "inoutsetdialog.h"
#include "ui_inoutsetdialog.h"
#include <QMessageBox>
#include <QDebug>

InOutSetDialog::InOutSetDialog(int _RowCnt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InOutSetDialog),
    RowCnt(_RowCnt)
{
    ui->setupUi(this);
    ui->YesBtn->setDefault(true);
    connect(ui->YesBtn,SIGNAL(clicked(bool)),this,SLOT(GetInOut()));
    connect(ui->NoBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    setWindowTitle("设置出入口");
}

InOutSetDialog::~InOutSetDialog()
{
    delete ui;
}

void InOutSetDialog::GetInOut(){
    //qDebug() << "From Func GetInOut In InOutSetDialog with RowCnt" << RowCnt;
    bool InRange = ui->I1SpinBox->value()>=1 && ui->I1SpinBox->value()<=RowCnt &&
            ui->I2SpinBox->value()>=1 && ui->I2SpinBox->value()<=RowCnt &&
            ui->O1SpinBox->value()>=1 && ui->O1SpinBox->value()<=RowCnt &&
            ui->O2SpinBox->value()>=1 && ui->O2SpinBox->value()<=RowCnt &&
            ui->O3SpinBox->value()>=1 && ui->O3SpinBox->value()<=RowCnt;
    bool InRank = ui->I1SpinBox->value() < ui->I2SpinBox->value() &&
            ui->O1SpinBox->value() < ui->O2SpinBox->value() &&
            ui->O2SpinBox->value() < ui->O3SpinBox->value();
    if(InRange&&InRank) {
        I1=ui->I1SpinBox->value();
        I2=ui->I2SpinBox->value();
        O1=ui->O1SpinBox->value();
        O2=ui->O2SpinBox->value();
        O3=ui->O3SpinBox->value();
        emit SendInOut(I1,I2,O1,O2,O3);
        this->close();
    } else {
        //qDebug() << "From Func GetInOut In InOutSetDialog with RowCnt InRange InRank" << RowCnt <<InRange <<InRank;
        QMessageBox::critical(this,"输入不合法","请正确输入数据:\n出入口位置不应超出列范围;\n出入口位置不应重叠;\n出入口应由左到右依次排列;");
    }
}
