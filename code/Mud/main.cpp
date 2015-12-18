#include <QApplication>
#include <QSurface>
#include <QSurfaceFormat>
#include <QMainWindow>

#include "main.ih"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sidebar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setOpenGLVersion(majorOpenGLVersion, minorOpenGLVersion);

    // View (sort of)
    MainWindow w;
    Ui::MainWindow *ui = w.getUi();

    // Model
    Grid *grid = Grid::gridFactory(ui->sidebar->getGridType(),
                                   ui->sidebar->getGridTypeDistribution());

    // Controller
    GridController *gridController = new GridController(grid);

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
