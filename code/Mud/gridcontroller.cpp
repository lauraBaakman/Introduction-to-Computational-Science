#include "gridcontroller.h"

GridController::GridController(Grid *grid, GridSolver *gridSolver, Canvas *canvas, QObject *parent) :
    QObject(parent),
    grid(grid),
    gridSolver(gridSolver),
    canvas(canvas)
{
    //
}

void GridController::replaceGridSlot(Grid::Settings settings)
{
    qDebug() << "Replace grid slot...";
    grid->gridFactory(settings);
    emit energyChanged(grid->energy());

    delete gridSolver;
    this->gridSolver = new GridSolver(grid);

    canvas->reset();

    visualiseGrid();
}

void GridController::doBreak()
{
    (grid->*grid->breakSprings)();

    gridSolver->update();

    emit energyChanged(grid->energy());

    this->visualiseGrid();
}

void GridController::doSolve()
{
    gridSolver->solve();

    emit energyChanged(grid->energy());

    this->visualiseGrid();
}

void GridController::setBreakMethod(Grid::SpringBreakMethod method)
{
    grid->setBreakMethod(method);
}

void GridController::setBreakMethodParameter(float parameter)
{
    grid->setBreakMethodParameter(parameter);
}

void GridController::visualiseGrid()
{
    canvas->build(grid);
    canvas->update();
}
