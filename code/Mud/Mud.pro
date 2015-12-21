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
    canvas.cpp \
    sidebar.cpp \
    grid.cpp \
    gridcontroller.cpp \
    particle.cpp \
    spring.cpp

HEADERS  += mainwindow.h \
    main.ih \
    canvas.h \
    sidebar.h \
    grid.h \
    gridcontroller.h \
    particle.h \
    spring.h

FORMS  += mainwindow.ui \
        sidebar.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/armadillo/lib/release/ -larmadillo.6.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/armadillo/lib/debug/ -larmadillo.6.10.0
else:unix: LIBS += -L$$PWD/libs/armadillo/lib/ -larmadillo.6.10.0

INCLUDEPATH += $$PWD/libs/armadillo/include
DEPENDPATH += $$PWD/libs/armadillo/include
