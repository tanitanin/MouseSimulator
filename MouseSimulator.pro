#-------------------------------------------------
#
# Project created by QtCreator 2014-08-07T17:12:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MouseSimulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        mazeitem.cpp \
    mouseitem.cpp

HEADERS  += mainwindow.h \
            mazeitem.h \
    mouseitem.h

FORMS    += mainwindow.ui
