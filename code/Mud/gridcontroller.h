#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <QObject>

#include "grid.h"

class GridController : public QObject
{
    Q_OBJECT
public:
    explicit GridController(QObject *parent = 0);

private:
    Grid grid;

signals:

public slots:
};

#endif // GRIDCONTROLLER_H
