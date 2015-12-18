#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    qDebug() << "Constructor Grid";
}

Grid* Grid::gridFactory(Type type, TypeDistribution typeDistribution)
{
    switch(type)
    {
    case SQUARE:
        return selectGridCreator(typeDistribution, &uniformSquareGrid, &variableSquareGrid);
        break;
    case HEXAGONAL:
        return selectGridCreator(typeDistribution, &uniformHexagonalGrid, &variableHexagonalGrid);
        break;
    }
}

Grid* Grid::selectGridCreator(TypeDistribution typeDistribution, gridCreator uniform, gridCreator variable)
{
    switch(typeDistribution)
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



