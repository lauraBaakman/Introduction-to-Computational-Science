#ifndef GRID_H
#define GRID_H

#include <QObject>

class Grid : public QObject
{
    Q_OBJECT
public:
    enum Type {
        SQUARE,
        HEXAGONAL,
    };

    enum TypeDistribution {
        UNIFORM,
        VARIABLE
    };

    struct Settings {
        Type type;
        TypeDistribution typeDistribution;
//        int width;
//        int height;
    };

    explicit Grid(QObject *parent = 0);
    ~Grid();

    static Grid* gridFactory(Settings settings);

private:
    static Grid* uniformSquareGrid();
    static Grid* variableSquareGrid();

    static Grid* uniformHexagonalGrid();
    static Grid* variableHexagonalGrid();

    typedef Grid* (*gridCreator)();
    static Grid* selectGridCreator(Settings settings, gridCreator uniform, gridCreator variable);
signals:

public slots:
};

#endif // GRID_H
