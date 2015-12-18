#include "gridcontroller.h"

GridController::GridController(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid)
{
    qDebug() << "Constructor GridController";
}

void GridController::replaceGridSlot(Grid::Settings settings)
{
    qDebug() << "Replace grid slot...";
    delete grid;
    grid = Grid::gridFactory(settings);

}
