#-------------------------------------------------
#
# Project created by QtCreator 2015-12-25T12:57:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesignPatternIllustrator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    patterns/adapter.h \
    treecombobox.h

FORMS    += mainwindow.ui
