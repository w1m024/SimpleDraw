#-------------------------------------------------
#
# Project created by QtCreator 2023-07-19T10:57:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleDraw_19_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    centerwidget.cpp \
    ellipse.cpp \
    line.cpp \
    point.cpp \
    rectangle.cpp \
    shape.cpp

HEADERS  += mainwindow.h \
    centerwidget.h \
    ellipse.h \
    line.h \
    point.h \
    rectangle.h \
    shape.h

CONFIG+=C++11
