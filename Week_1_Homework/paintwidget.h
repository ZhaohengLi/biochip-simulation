#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>


namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void SetAll(int,int,int,int,int,int);
    void SetRowCnt(int);
    void SetInOut(int,int,int,int,int);
    void StartPaint(QGraphicsScene *_Scene);

private:
    Ui::PaintWidget *ui;

    int RowCnt=5;
    int I1=2,I2=4,O1=1,O2=3,O3=5;
    int TotalId=0;

    QGraphicsScene *Scene;

public slots:
    void SetViewScale(QString);

signals:
    void StatusChanged(int,double);
    void SetHelpText(QString);
    void RestoreInOut();
};

#endif // PAINTWIDGET_H
