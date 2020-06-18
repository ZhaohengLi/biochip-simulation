#include "allsetdialog.h"
#include "ui_allsetdialog.h"
#include <QMessageBox>

AllSetDialog::AllSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSetDialog)
{
    ui->setupUi(this);
    connect(ui->YesBtn,SIGNAL(clicked(bool)),this,SLOT(GetAllSet()));
    connect(ui->NoBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    ui->YesBtn->setDefault(true);
    setWindowTitle("设置所有");
}

AllSetDialog::~AllSetDialog()
{
    delete ui;
}

void AllSetDialog::GetAllSet(){
    bool Rowok = ui->RowSpinBox->value() >= 5 && ui->RowSpinBox->value() <=8;
    bool InRange = ui->I1SpinBox->value()>=1 && ui->I1SpinBox->value()<=ui->RowSpinBox->value() &&
            ui->I2SpinBox->value()>=1 && ui->I2SpinBox->value()<=ui->RowSpinBox->value() &&
            ui->O1SpinBox->value()>=1 && ui->O1SpinBox->value()<=ui->RowSpinBox->value() &&
            ui->O2SpinBox->value()>=1 && ui->O2SpinBox->value()<=ui->RowSpinBox->value() &&
            ui->O3SpinBox->value()>=1 && ui->O3SpinBox->value()<=ui->RowSpinBox->value();
    bool InRank = ui->I1SpinBox->value() < ui->I2SpinBox->value() &&
            ui->O1SpinBox->value() < ui->O2SpinBox->value() &&
            ui->O2SpinBox->value() < ui->O3SpinBox->value();

    if(Rowok&&InRange&&InRank) {
        int RowCnt=ui->RowSpinBox->value();
        int I1=ui->I1SpinBox->value();
        int I2=ui->I2SpinBox->value();
        int O1=ui->O1SpinBox->value();
        int O2=ui->O2SpinBox->value();
        int O3=ui->O3SpinBox->value();
        emit SendAllSet(RowCnt,I1,I2,O1,O2,O3);
        this->close();
    } else {
        //qDebug() << "From Func GetInOut In InOutSetDialog with RowCnt InRange InRank" << RowCnt <<InRange <<InRank;
        QMessageBox::critical(this,"输入不合法","请正确输入数据:\n行列数 X 应为 [5,8] 之间的整数;\n出入口位置不应超出列范围;\n出入口位置不应重叠;\n出入口应由左到右依次排列;");
    }

}
