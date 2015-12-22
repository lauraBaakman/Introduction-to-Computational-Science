#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "grid.h"
#include "gridsolver.h"
#include "canvas.h"

class GridController : public QObject
{
    Q_OBJECT
public:
    GridController(Grid *grid, GridSolver *gridSolver, Canvas *canvas, QObject *parent = 0);

private:
    Grid *grid;
    GridSolver *gridSolver;
    Canvas *canvas;

    void visualiseGrid();

signals:

public slots:
    void replaceGridSlot(Grid::Settings settings);
};

#endif // GRIDCONTROLLER_H
