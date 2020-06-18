#include "paintwidget.h"
#include "ui_paintwidget.h"
#include "tubeitem.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <algorithm>
#include <QMessageBox>
#include <QString>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintWidget)
{
    ui->setupUi(this);
    RowCnt=5; I1=2; I2=4; O1=1; O2=3; O3=5;

    Scene = new QGraphicsScene(this);
    ui->View->setScene(Scene);
    ui->View->scale(0.8,0.8);
    StartPaint(Scene);
}//构造函数

PaintWidget::~PaintWidget()
{
    delete ui;
}//析构函数

void PaintWidget::SetAll(int _Rowcnt, int _I1, int _I2, int _O1, int _O2, int _O3){
    RowCnt = _Rowcnt; I1 = _I1; I2 = _I2; O1 = _O1; O2 = _O2; O3 = _O3;
    StartPaint(this->Scene);
}//设置全部参数 改变值 重新绘制

void PaintWidget::SetRowCnt(int _RowCnt){
    RowCnt = _RowCnt;
    StartPaint(this->Scene);
    //qDebug()<< "From Func SetRowCnt In PaintWidget With RowCnt" << RowCnt;
}//设置行列数 改变值 重新绘制

void PaintWidget::SetInOut(int _I1, int _I2, int _O1, int _O2, int _O3){
    I1 = _I1; I2 = _I2; O1 = _O1; O2 = _O2; O3 = _O3;
    StartPaint(this->Scene);
    //qDebug()<< "From Func SetInOut In Paintwidget With temp value" << _I1 << _I2 << _O1 << _O2 << _O3;
    //qDebug()<< "From Func SetInOut In Paintwidget With actu value" << this->I1 << this->I2 << this->O1 << this->O2 << this->O3;
}//设置出入口位置 改变值 重新绘制

void PaintWidget::StartPaint(QGraphicsScene *_Scene){
    //qDebug()<< "From Func StartPaint in PaintWidget with" << this->RowCnt << this->I1 << this->I2 << this->O1 << this->O2 << this->O3;
    _Scene->clear();//首先清理场景

    QGraphicsItem *item = new QGraphicsRectItem(-40,-10,(RowCnt-1)*90+90,RowCnt*90+80+20);
    _Scene->addItem(item);//加入参考框
    QGraphicsItem *item2 = new QGraphicsRectItem(-43,-13,(RowCnt-1)*90+97,RowCnt*90+80+27);
    _Scene->addItem(item2);//加入参考框

    for(int i=0; i<this->RowCnt; i++){
        int x=i*90;
        for(int j=0; j<this->RowCnt; j++){
            QGraphicsItem *tempitem = new QGraphicsRectItem(x,(80+j*90),10,10);
            //tempitem->setBrush(QBrush(QColor(Qt::gray)));
            //tempitem->setRect(QRectF(x,(80+j*90),10,10));
            _Scene->addItem(tempitem);
        }
    }//结点正方形10*10

    TotalId=0;//设置ID
    for(int i=0; i<this->RowCnt; i++){
        int x=i*90;
        for(int j=0; j<this->RowCnt-1; j++){
            TubeItem *tempitem = new TubeItem(x,90+j*90,10,80,2*(j+1),2*i+1,TotalId++);
            _Scene->addItem(tempitem);
            connect(tempitem,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        }
    }//竖直管道铺设
    for(int i=0; i<this->RowCnt-1;i++){
        int x=10+i*90;
        for(int j=0; j<this->RowCnt; j++){
            TubeItem *tempitem = new TubeItem(x,80+90*j,80,10,2*j+1,(i+1)*2,TotalId++);
            _Scene->addItem(tempitem);
            connect(tempitem,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        }
    }//水平管道铺设

    if(this->I2 <= this->RowCnt && this->O3 <= this->RowCnt){
        TubeItem *I1item = new TubeItem((this->I1-1)*90,0,10,80,0,2*this->I1-1,TotalId++);
        _Scene->addItem(I1item);
        connect(I1item,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        TubeItem *I2item = new TubeItem((this->I2-1)*90,0,10,80,0,2*this->I2-1,TotalId++);
        _Scene->addItem(I2item);
        connect(I2item,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));

        TubeItem *O1item = new TubeItem((this->O1-1)*90,90*this->RowCnt,10,80,99,2*this->O1-1,TotalId++);
        _Scene->addItem(O1item);
        connect(O1item,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        TubeItem *O2item = new TubeItem((this->O2-1)*90,90*this->RowCnt,10,80,99,2*this->O2-1,TotalId++);
        _Scene->addItem(O2item);
        connect(O2item,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        TubeItem *O3item = new TubeItem((this->O3-1)*90,90*this->RowCnt,10,80,99,2*this->O3-1,TotalId++);
        _Scene->addItem(O3item);
        connect(O3item,SIGNAL(StatusChanged(int,double)),this,SIGNAL(StatusChanged(int,double)));
        emit SetHelpText("单击以去除/添加管道\n右击以设置管道宽度...");
    } else {
        emit RestoreInOut();
    }
    TotalId--;

}

void PaintWidget::SetViewScale(QString _ScaleRate){
    double rate = _ScaleRate.toDouble();
    //qDebug()<< "From Func SetViewScale In Paintwidget With rate" << rate;
    ui->View->scale(rate,rate);
    ui->View->repaint();
}





