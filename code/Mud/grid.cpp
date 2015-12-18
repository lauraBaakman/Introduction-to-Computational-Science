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

Grid* Grid::gridFactory(Settings settings)
{
    switch(settings.type)
    {
    case SQUARE:
        return selectGridCreator(settings, &uniformSquareGrid, &variableSquareGrid);
        break;
    case HEXAGONAL:
        return selectGridCreator(settings, &uniformHexagonalGrid, &variableHexagonalGrid);
        break;
    }
}

Grid* Grid::selectGridCreator(Settings settings, gridCreator uniform, gridCreator variable)
{
    switch(settings.typeDistribution)
    {
    case UNIFORM:
        return uniform();
        break;
    case VARIABLE:
        return variable();
        break;
    }
}

Grid* Grid::uniformSquareGrid()
{
    qDebug() << "uniformSquareGrid! Not implemented yet!";
    return new Grid();
}

Grid* Grid::variableSquareGrid()
{
    qDebug() << "variableSquareGrid! Not implemented yet!";
    return new Grid();
}

Grid* Grid::uniformHexagonalGrid()
{
    qDebug() << "uniformHexagonalGrid! Not implemented yet!";
    return new Grid();
}

Grid* Grid::variableHexagonalGrid()
{
    qDebug() << "variableHexagonalGrid! Not implemented yet!";
    return new Grid();
}



