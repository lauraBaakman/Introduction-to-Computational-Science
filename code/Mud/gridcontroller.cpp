#include "gridcontroller.h"

GridController::GridController(Grid *grid, GridSolver *gridSolver, Canvas *canvas, QObject *parent) :
    QObject(parent),
    grid(grid),
    gridSolver(gridSolver),
    canvas(canvas)
{
    //qDebug() << "Constructor GridController";
}

void GridController::replaceGridSlot(Grid::Settings settings)
{
    qDebug() << "Replace grid slot...";
    grid->gridFactory(settings);
    visualiseGrid();
}

void GridController::doStep()
{
    // Break springs?

    // solver solve grid

    // this->visualiseGrid();
}

void GridController::visualiseGrid()
{
    canvas->build(grid);
    canvas->update();
}
