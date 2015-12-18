#include "gridcontroller.h"

GridController::GridController(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid)
{
    qDebug() << "Constructor GridController";
}

void GridController::replaceGridSlot(Grid::Settings settings)
{
    qDebug() << (int)settings.type;

}
