#-------------------------------------------------
#
# Project created by QtCreator 2014-04-13T15:45:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSZT-Hexxagon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp \
    Field.cpp \
    DataPack.cpp

HEADERS  += mainwindow.h \
    model.h \
    Field.h \
    DataPack.h

FORMS    += mainwindow.ui
