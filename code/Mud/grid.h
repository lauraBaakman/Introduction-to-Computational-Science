#ifndef GRID_H
#define GRID_H

#include <QObject>

class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(QObject *parent = 0);

    enum Type {
        SQUARE,
        HEXAGONAL,
    };

    enum TypeDistribution {
        UNIFORM,
        VARIABLE
    };

    static Grid* gridFactory(Type type, TypeDistribution typeDistribution);

private:
    static Grid* uniformSquareGrid();
    static Grid* variableSquareGrid();

    static Grid* uniformHexagonalGrid();
    static Grid* variableHexagonalGrid();

    typedef Grid* (*gridCreator)();
    static Grid* selectGridCreator(TypeDistribution typeDistribution, gridCreator uniform, gridCreator variable);
signals:

public slots:
};

#endif // GRID_H
