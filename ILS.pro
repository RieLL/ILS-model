#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T19:12:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ILS
TEMPLATE = app

QMAKE_LFLAGS += "-s -static-libgcc -static-libstdc++ -static"
QMAKE_CXXFLAGS += "-std=c++11 -std=gnu++11 -s -static-libgcc -static-libstdc++ -static"

SOURCES  +=             \
    src/main.cpp        \
    src/mainwindow.cpp  \
    src/data.cpp \
    src/plot/plotmanager.cpp \
    src/plot/plot/variables.cpp \
    src/plot/plot/signature.cpp \
    src/plot/plot/grid.cpp \
    src/plot/plot/axis.cpp \
    src/plot/plot/plotTypes/spectrum.cpp \
    src/plot/plot/plotTypes/dots.cpp \
    src/plot/plot/virtual/window.cpp \
    src/plot/plot/virtual/scale.cpp \
    src/plot/plot/virtual/mainparameters.cpp \
    src/plot/plot/virtual/hairstroke.cpp \
    src/image/image.cpp \
    src/plot/plot/plot.cpp \
    src/function/function.cpp

HEADERS  +=             \
    src/mainwindow.h    \
    src/data.h \
    src/plot/plotmanager.h \
    src/plot/plot/variables.h \
    src/plot/plot/signature.h \
    src/plot/plot/grid.h \
    src/plot/plot/axis.h \
    src/plot/plot/plotTypes/spectrum.h \
    src/plot/plot/plotTypes/dots.h \
    src/plot/plot/virtual/window.h \
    src/plot/plot/virtual/scale.h \
    src/plot/plot/virtual/mainparameters.h \
    src/plot/plot/virtual/hairstroke.h \
    src/image/image.h \
    src/plot/plot/plot.h \
    src/function/function.h

FORMS    += src/mainwindow.ui

RESOURCES +=            \
    res.qrc

RC_FILE = res/bsaa_ils.rc
