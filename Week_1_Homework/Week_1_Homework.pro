#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T14:50:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Week_1_Homework
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rowcolsetdialog.cpp \
    inoutsetdialog.cpp \
    paintwidget.cpp \
    tubeitem.cpp \
    widthsetdialog.cpp \
    allsetdialog.cpp \
    readalldialog.cpp


HEADERS += \
        mainwindow.h \
    rowcolsetdialog.h \
    inoutsetdialog.h \
    paintwidget.h \
    cal.h \
    tubeitem.h \
    widthsetdialog.h \
    allsetdialog.h \
    readalldialog.h


FORMS += \
        mainwindow.ui \
    rowcolsetdialog.ui \
    inoutsetdialog.ui \
    paintwidget.ui \
    widthsetdialog.ui \
    allsetdialog.ui \
    readalldialog.ui


RESOURCES += \
    icons.qrc
