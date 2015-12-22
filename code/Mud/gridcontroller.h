#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "grid.h"

class GridController : public QObject
{
    Q_OBJECT
public:
    GridController(Grid *grid, QObject *parent = 0);

private:
    Grid *grid;

signals:

public slots:
    void replaceGridSlot(Grid::Settings settings);
};

#endif // GRIDCONTROLLER_H
