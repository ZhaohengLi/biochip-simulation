#include "rowcolsetdialog.h"
#include "ui_rowcolsetdialog.h"

#include <QMessageBox>

RowColSetDialog::RowColSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowColSetDialog),
    RowCnt(5)
{
    ui->setupUi(this);
    setWindowTitle("设置行列数");
    init();
}//默认构造函数

RowColSetDialog::RowColSetDialog(int _RowCnt, QWidget *parent):
    QDialog(parent),
    ui(new Ui::RowColSetDialog),
    RowCnt(_RowCnt)
{
    ui->setupUi(this);
    init();
}//带参构造函数

void RowColSetDialog::init(){
    ui->YesBtn->setDefault(true);
    connect(ui->YesBtn,SIGNAL(clicked(bool)),this,SLOT(GetRowCol()));
    connect(ui->NoBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
}//构造函数的内函数

RowColSetDialog::~RowColSetDialog()
{
    delete ui;
}//析构函数

void RowColSetDialog::GetRowCol(){
    if(ui->RowSpinBox->value() >= 5 && ui->RowSpinBox->value() <=8){
        RowCnt = ui->RowSpinBox->value();
        emit SendRowCol(RowCnt);
        this->close();
    } else {
        QMessageBox::critical(this,"输入不合法","请正确输入行列数！");
    }
}//槽函数 检查输入 发出信号




