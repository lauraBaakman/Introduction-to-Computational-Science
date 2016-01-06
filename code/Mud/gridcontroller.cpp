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

    delete gridSolver;
    this->gridSolver = new GridSolver(grid);

    canvas->reset();

    visualiseGrid();
}

void GridController::doBreak()
{
    qDebug() << "doBreak()";
    // Break springs?
    qDebug() << "Grid (before) energy: "<< grid->energy();
    (grid->*grid->breakSprings)();

    gridSolver->update();

    qDebug() << "Grid (after) energy: "<< grid->energy();
    this->visualiseGrid();
}

void GridController::doSolve()
{
    qDebug() << "doSolve()";
    qDebug() << "Grid (before) energy: "<< grid->energy();
    // solver solve grid
    gridSolver->solve();

    qDebug() << "Grid (after) energy: "<< grid->energy();
    this->visualiseGrid();
}

void GridController::visualiseGrid()
{
    canvas->build(grid);
    canvas->update();
}
