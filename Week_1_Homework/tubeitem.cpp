#include "tubeitem.h"
#include "widthsetdialog.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include <QList>

TubeItem::TubeItem(int x, int y, int w, int h, int i, int j, int id):
    x(x),y(y),w(w),h(h),i(i),j(j),id(id)
{
    setAcceptDrops(true);
    setToolTip("单击以去除/添加管道，右击以设置管道宽度。");
    Color = QColor(Qt::gray);
}

QRectF TubeItem::boundingRect() const{
    return QRect(x,y,w,h);
}

void TubeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(DragOver ? Color.light(130) : Color);
    painter->drawRect(x,y,w,h);
}

void TubeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //qDebug()<< "From Func mousePressEvent in TubeItem";
    if(event->button() == Qt::LeftButton){
        UpdateState();
    }
    if(event->button() == Qt::RightButton){
        if(this->State==1){
            WidthSetDialog *wsd = new WidthSetDialog();
            wsd->show();
            connect(wsd,SIGNAL(SendWidth(int)),this,SLOT(SetArgus(int)));
            //qDebug()<<"From if rightbutton pressed in TubeItem with x y w h i j id c State" << x <<"    "<< y <<"    "<<w <<"    "<<h <<"    "<<i<<"     "<< j<<"    "<< id <<"    "<< c <<"    "<< State;
        }
    }
}

void TubeItem::UpdateState(){
    State = State ^ 1;
    Color = State? QColor(Qt::gray) : QColor(Qt::white);
    update();
    if(State==1 && c>0) {
        emit StatusChanged(id,c);
        //qDebug()<<"From Func UpdateState in TubeItem with emit StatusChanged(id,c)" <<id <<c;

    } else {
        emit StatusChanged(id,State);
        //qDebug()<<"From Func UpdateState in TubeItem with emit StatusChanged(id,State)" <<id <<State;

    }
}

void TubeItem::SetArgus(int _neww){
    //qDebug()<<"From Func SetArgus in TubeItem with id pre_c" << id << c;
    this-> c = double(200.0/double(_neww));
    //qDebug()<<"From Func SetArgus in TubeItem with id c" << id << c;

    if(this->j%2==1){
        this->x=x+(w-_neww/20)/2;
        this->w=_neww/20;
    }
    if(this->i%2==1){
        this->y=y+(h-_neww/20)/2;
        this->h=_neww/20;
    }
    update();

    if(CheckCollisions()==true){
        //qDebug() << "From Func SetArgus in TubeItem with CheckCollosions==ture";
    } else {
        emit StatusChanged(this->id,this->c);
        //qDebug()<<"From Func SetArgus in TubeItem with emit StatusChanged(id,c)" <<id <<c;
    }
}

bool TubeItem::CheckCollisions(){
    /*QList<QGraphicsItem *> collisions = collidingItems(Qt::IntersectsItemBoundingRect);
    foreach (QGraphicsItem *collidingItem, collisions) {
        TubeItem *tempitem = static_cast<TubeItem*> (collidingItem);
        //qDebug()<<"From Func CheckCollisions in TubeItem with i j" << tempitem->i << tempitem->j;
        }*/
    return false;
}





