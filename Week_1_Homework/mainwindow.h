#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rowcolsetdialog.h"
#include "inoutsetdialog.h"
#include "allsetdialog.h"

#include <vector>
#include <QSignalMapper>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int RowCnt=5,I1=2,I2=4,O1=1,O2=3,O3=5;
    double *TubeStatus;

    void InitActions();

    RowColSetDialog *rcsd;
    InOutSetDialog *iosd;
    AllSetDialog *asd;
    QSignalMapper *mapper;

public slots:
    void SetRowCol(int);
    void SetInOut(int,int,int,int,int);
    void SetAll(int,int,int,int,int,int);
    void Cal();
    void InitTubeStatus();
    void SetTubeStatus(int _Index, double _Status);
    void SetHelpText(QString);
    void RestoreInOut();


private slots:
    void CallRowColSetDialog();
    void CallInOutSetDialog();
    void CallAllSetDialog();
    void CallReadAllDialog();
};

#endif // MAINWINDOW_H
