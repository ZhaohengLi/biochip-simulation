#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rowcolsetdialog.h"
#include "inoutsetdialog.h"
#include "allsetdialog.h"
#include "cal.h"
#include "readalldialog.h"

#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->RowColSetBtn,SIGNAL(clicked(bool)),this,SLOT(CallRowColSetDialog()));
    connect(ui->InOutSetBtn,SIGNAL(clicked(bool)),this,SLOT(CallInOutSetDialog()));
    connect(ui->CloseBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->CalBtn,SIGNAL(clicked(bool)),this,SLOT(Cal()));
    connect(ui->GetPaintWidget,SIGNAL(StatusChanged(int,double)),this,SLOT(SetTubeStatus(int,double)));
    connect(ui->AllBtn,SIGNAL(clicked(bool)),this,SLOT(CallAllSetDialog()));
    connect(ui->ReadAllBtn,SIGNAL(clicked(bool)),this,SLOT(CallReadAllDialog()));
    connect(ui->GetPaintWidget,SIGNAL(RestoreInOut()),this,SLOT(RestoreInOut()));
    connect(ui->GetPaintWidget,SIGNAL(SetHelpText(QString)),this,SLOT(SetHelpText(QString)));

    ui->AllBtn->setIcon(QIcon(":/Settings/AllSetIcon"));
    ui->RowColSetBtn->setIcon(QIcon(":/Settings/RowColIcon"));
    ui->InOutSetBtn->setIcon(QIcon(":/Settings/InOutIcon"));
    ui->CalBtn->setIcon(QIcon(":/Cal/Cal"));
    ui->CloseBtn->setIcon(QIcon(":/new/Close"));
    ui->x12Btn->setIcon(QIcon(":/new/x12"));
    ui->x08Btn->setIcon(QIcon(":/new/x08"));

    mapper = new QSignalMapper(this);
    connect(ui->x08Btn,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    mapper->setMapping(ui->x08Btn,"0.8");
    connect(ui->x12Btn,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    mapper->setMapping(ui->x12Btn,"1.2");
    connect(mapper,SIGNAL(mapped(QString)),ui->GetPaintWidget,SLOT(SetViewScale(QString)));

    InitActions();
    InitTubeStatus();
    SetHelpText("目前程序运行正常...");
    SetHelpText("单击以去除/添加管道\n右击以设置管道宽度...");

}//构造函数

void MainWindow::InitActions(){
    QAction *SetRowColAct = new QAction(this);
    connect(SetRowColAct,SIGNAL(triggered(bool)),this,SLOT(CallRowColSetDialog()));
    SetRowColAct->setIcon(QIcon(":/Settings/RowColIcon"));
    SetRowColAct->setIconText("行列数");
    SetRowColAct->setToolTip("用于设置芯片的行列数");
    SetRowColAct->setStatusTip("用于设置芯片的行列数");

    QAction *SetInOutAct = new QAction(QIcon(":/Settings/InOutIcon"),"出入口",this);
    connect(SetInOutAct,SIGNAL(triggered(bool)),this,SLOT(CallInOutSetDialog()));
    SetInOutAct->setToolTip("用于设置芯片的出入口位置");
    SetInOutAct->setStatusTip("用于设置芯片的出入口位置");

    QMenu *CreatMenu = menuBar()->addMenu("Creat Settings");
    QMenu *HelpMenu = menuBar()->addMenu("Help");
    HelpMenu->addAction(SetInOutAct);

    ui->mainToolBar->addAction(SetRowColAct);
    ui->mainToolBar->addAction(SetInOutAct);
    CreatMenu->addAction(SetInOutAct);
    CreatMenu->addAction(SetRowColAct);
}//构造函数内函数 用于建立QActions

MainWindow::~MainWindow(){
    delete ui;
}//析构函数

void MainWindow::CallRowColSetDialog(){
    rcsd = new RowColSetDialog(this);
    connect(rcsd,SIGNAL(SendRowCol(int)),this,SLOT(SetRowCol(int)));
    rcsd->exec();
}//槽函数 唤出行列设置对话框 聆听其发出的信号 进而设置行列数

void MainWindow::CallInOutSetDialog(){
    //qDebug()<< "From Func CallInOutSetDialog In MainWindow";
    iosd = new InOutSetDialog(RowCnt,this);
    connect(iosd,SIGNAL(SendInOut(int,int,int,int,int)),this,SLOT(SetInOut(int,int,int,int,int)));
    iosd->exec();
}//槽函数 唤出出入口设置对话框 聆听其发出的信号 进而设置出入口

void MainWindow::CallAllSetDialog(){
    asd = new AllSetDialog(this);
    connect(asd,SIGNAL(SendAllSet(int,int,int,int,int,int)),this,SLOT(SetAll(int,int,int,int,int,int)));
    asd->exec();
}//槽函数 唤出设置所有对话框 聆听其发出的信号 进而设置所有参数

void MainWindow::SetRowCol(int _RowCnt){
    RowCnt = _RowCnt;
    InitTubeStatus();
    ui->RowLcdNumber->display(RowCnt);
    ui->GetPaintWidget->SetRowCnt(RowCnt);
    //qDebug()<< "From Func SetRowCol In MainWindow With" << RowCnt;
}//设置行列数 初始化管道状态数据 开始画图

void MainWindow::SetInOut(int _I1, int _I2, int _O1, int _O2, int _O3){
    I1=_I1; I2=_I2; O1=_O1; O2=_O2; O3=_O3;
    InitTubeStatus();
    ui->I1Lcd->display(I1);
    ui->I2Lcd->display(I2);
    ui->O1Lcd->display(O1);
    ui->O2Lcd->display(O2);
    ui->O3Lcd->display(O3);
    ui->GetPaintWidget->SetInOut(I1,I2,O1,O2,O3);
    //qDebug()<< "From Func SetInOut In MainWindow With" << I1 << I2 << O1 << O2 << O3;
}//设置出入口 初始化管道状态数据 开始画图

void MainWindow::SetAll(int _RowCnt, int _I1, int _I2, int _O1, int _O2, int _O3){
    RowCnt = _RowCnt; I1=_I1; I2=_I2; O1=_O1; O2=_O2; O3=_O3;
    InitTubeStatus();
    ui->RowLcdNumber->display(RowCnt);
    ui->I1Lcd->display(I1);
    ui->I2Lcd->display(I2);
    ui->O1Lcd->display(O1);
    ui->O2Lcd->display(O2);
    ui->O3Lcd->display(O3);
    ui->GetPaintWidget->SetAll(RowCnt,I1,I2,O1,O2,O3);
}//设置所有参数 初始化管道状态数据 开始画图

void MainWindow::Cal(){
    //qDebug()<< "From Func Cal In MainWindow";
    QMessageBox::information(this,"注意排布","请确认正确创建管道排布:\n应有出入口且出入口应与管道联通;");
    int n=RowCnt;
    //qDebug()<< n;
    vector<double> leng(2*n*n-2*n+5,0);
    for(int i=0; i<2*n*n-2*n+5; i++){
        leng[i]=TubeStatus[i];
        //qDebug()<<TubeStatus[i];
        //qDebug()<<leng[i];
    }
    vector<double> ans = caluconspeed(n,leng,I1-1,I2-1,O1-1,O2-1,O3-1);
    //qDebug() << "ans" << ans[0] << ans[1] << ans[2];
    ui->O1ResLineEdit->setText(QString::number(ans[0]));
    ui->O2ResLineEdit->setText(QString::number(ans[1]));
    ui->O3ResLineEdit->setText(QString::number(ans[2]));
    if(ans[0]+ans[1]+ans[2]>399.0 && ans[0]+ans[1]+ans[2]<401.0){ SetHelpText("计算结果正常..."); }
    else{SetHelpText("计算结果不正常，请检查管道排布，可能出现问题...\n应有出入口且出入口应与管道联通");}
}//计算并输出结果

void MainWindow::InitTubeStatus(){
    //TubeStatus = new std::vector<double>(2*RowCnt*RowCnt-2*RowCnt+5,1);
    TubeStatus = new double[2*RowCnt*RowCnt-2*RowCnt+5];
    for(int i=0; i<2*RowCnt*RowCnt-2*RowCnt+5; i++){
        TubeStatus[i] = 1;
    }
    //qDebug() << "From Func InitTubeStatus In MainWindow with";
    //TubeStatus = vector<double>(2*RowCnt*RowCnt-2*RowCnt+5,1);

}
void MainWindow::SetTubeStatus(int _Index, double _Status){
    //qDebug() << "From Func SetTubeStatus In MainWindow with _index _Status" << _Index << _Status;
    TubeStatus[_Index] = _Status;
    //qDebug() << "From Func SetTubeStatus In MainWindow with index Status" << TubeStatus[_Index];
}

void MainWindow::SetHelpText(QString _HelpText){
    QDateTime ct = QDateTime::currentDateTime();
    QString time=ct.toString();
    ui->HelpTextEdit->append("-----------------------------\n"+time+"\n"+_HelpText+"\n-----------------------------\n");
}

void MainWindow::CallReadAllDialog(){
    ReadAllDialog *rad = new ReadAllDialog(this);
    rad->show();
}
void MainWindow::RestoreInOut(){
    RowCnt=5;I1=2;I2=4;O1=1;O2=3;O3=5;
    InitTubeStatus();
    SetAll(RowCnt,I1,I2,O1,O2,O3);
    QMessageBox::critical(this,"出入口位置错误","出入口位置已超出列范围:\n恢复为默认出入口位置;");
    SetHelpText("出入口位置已超出列范围\n已恢复为默认出入口位置...");
}
