#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

#include "grid.h"

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = 0);
    ~Sidebar();

    Grid::Type getGridType() const;
    Grid::TypeDistribution getGridTypeDistribution() const;

signals:
    void initGrid(int value);

private slots:
    void on_initApplyButton_clicked();

private:
    Ui::Sidebar *ui;
};

#endif // SIDEBAR_H
