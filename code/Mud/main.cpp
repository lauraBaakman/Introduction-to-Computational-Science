#include <QApplication>
#include <QSurface>
#include <QSurfaceFormat>

#include "main.ih"
#include "mainwindow.h"
#include "sidebar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setOpenGLVersion(majorOpenGLVersion, minorOpenGLVersion);

    MainWindow w;
//    w.init();
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
