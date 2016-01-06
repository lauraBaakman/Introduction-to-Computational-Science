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
    void energyChanged(float energy);

public slots:
    void replaceGridSlot(Grid::Settings settings);
    void doBreak();
    void doSolve();
    void setBreakMethod(Grid::SpringBreakMethod method);
    void setBreakMethodParameter(float parameter);
};

#endif // GRIDCONTROLLER_H
