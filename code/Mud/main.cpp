#include <QApplication>
#include <QSurface>
#include <QSurfaceFormat>
#include <QMainWindow>
#include <QObject>
#include <QDebug>

#include "main.ih"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sidebar.h"
#include "gridsolver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setOpenGLVersion(majorOpenGLVersion, minorOpenGLVersion);

    MainWindow w;
    w.show();

    return a.exec();
}

void setOpenGLVersion(int const majorVersion, int const minorVersion)
{
    QSurfaceFormat glFormat;
    glFormat.setProfile(QSurfaceFormat::CoreProfile);

    glFormat.setVersion(majorVersion, minorVersion);
    glFormat.setOption(QSurfaceFormat::DebugContext);

    QSurfaceFormat::setDefaultFormat(glFormat);
}
