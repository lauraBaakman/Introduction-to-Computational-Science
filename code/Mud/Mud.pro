#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T11:09:50
#
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10
QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -isystem /usr/local/include

QMAKE_LFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mud
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    sidebar.cpp \
    grid.cpp \
    gridcontroller.cpp \
    particle.cpp \
    spring.cpp \
    gridsolver.cpp \
    fixedparticle.cpp \
    freeparticle.cpp

HEADERS  += mainwindow.h \
    main.ih \
    canvas.h \
    sidebar.h \
    grid.h \
    gridcontroller.h \
    particle.h \
    spring.h \
    gridsolver.h \
    fixedparticle.h \
    freeparticle.h

FORMS  += mainwindow.ui \
        sidebar.ui

macx: LIBS += -L/usr/local/lib/ -larmadillo.6.40.3

DEPENDPATH += /usr/local/include

RESOURCES += \
    resources.qrc

