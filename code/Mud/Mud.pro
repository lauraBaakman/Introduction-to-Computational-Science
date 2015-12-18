#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T11:09:50
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10
QMAKE_LFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mud
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
    main.ih \
    canvas.h

FORMS    += mainwindow.ui
