#ifndef TUBEITEM_H
#define TUBEITEM_H
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QObject>

class TubeItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    int x=-1,y=-1,w=-1,h=-1,i=-1,j=-1,id=-1,State=1;
    double c = -1.0;
    TubeItem(int x,int y,int w, int h, int i,int j,int id);
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void UpdateState();
    bool CheckCollisions();
    //void Fix

private:
    QColor Color;
    bool DragOver;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void SetArgus(int);

signals:
    void StatusChanged(int,double);
};

#endif // TUBEITEM_H
