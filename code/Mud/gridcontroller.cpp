#include "gridcontroller.h"

GridController::GridController(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid)
{
    qDebug() << "Constructor GridController";
}

void GridController::replaceGrid(int value)
{
    qDebug() << "BLEH";
}
