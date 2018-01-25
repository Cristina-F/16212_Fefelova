#-------------------------------------------------
#
# Project created by QtCreator 2017-12-22T20:40:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app
QMAKE_CXXFLAGS= -std=gnu++11

SOURCES += main.cpp\
        Window.cpp \
    RenderArea.cpp\
    Field.cpp \
    Model.cpp\
    History.cpp \
    Controller.cpp \
    FormatRLE.cpp \


HEADERS  += \
    Window.h \
    RenderArea.h\
    Field.h \
    Model.h \
    History.h \
    Controller.h \
    FormatRLE.h \


DISTFILES += \
    l1.rle\
    life.rle \
    g.rle

