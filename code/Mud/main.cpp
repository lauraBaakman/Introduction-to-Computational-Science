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

    // View (sort of)
    MainWindow w;
    // TODO: Litte weird?
    Ui::MainWindow *ui = w.getUi();

    // Model
    Grid *grid = new Grid();
    grid->gridFactory(ui->sidebar->getGridSettings());

    qDebug() << *grid;

    // Controller
    GridController *gridController = new GridController(grid);

    GridSolver *solver = new GridSolver(grid);

//    qDebug() << *grid;

    QObject::connect(ui->sidebar, SIGNAL(replaceGridSignal(Grid::Settings)),
                     gridController, SLOT(replaceGridSlot(Grid::Settings)));

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
