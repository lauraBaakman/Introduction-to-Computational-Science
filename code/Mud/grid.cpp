#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    qDebug() << "Constructor Grid";
}

Grid::~Grid()
{
     qDebug() << "Destructor Grid";
}

void Grid::gridFactory(Settings settings)
{
    switch(settings.type)
    {
    case SQUARE:
        selectGridCreator(settings, &Grid::uniformSquareGrid, &Grid::variableSquareGrid);
        break;
    case HEXAGONAL:
        selectGridCreator(settings, &Grid::uniformHexagonalGrid, &Grid::variableHexagonalGrid);
        break;
    }
}

void Grid::selectGridCreator(Settings settings, gridCreator uniform, gridCreator variable)
{
    switch(settings.typeDistribution)
    {
    case UNIFORM:
        (this->*uniform)();
        break;
    case VARIABLE:
        (this->*variable)();
        break;
    }
}

void Grid::uniformSquareGrid()
{
    qDebug() << "uniformSquareGrid! Not implemented yet!";
}

void Grid::variableSquareGrid()
{
    qDebug() << "variableSquareGrid! Not implemented yet!";
}

void Grid::uniformHexagonalGrid()
{
    qDebug() << "uniformHexagonalGrid! Not implemented yet!";
}

void Grid::variableHexagonalGrid()
{
    qDebug() << "variableHexagonalGrid! Not implemented yet!";
}



