#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grid.h"
#include "gridcontroller.h"
#include "gridsolver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    Ui::MainWindow *getUi() const;

private:
    Ui::MainWindow *ui;

    Grid *grid;
    GridController *gridController;
    GridSolver *gridSolver; // Maybe add this to the gridController..
    // Canvas/View => ui->canvas
};

#endif // MAINWINDOW_H
