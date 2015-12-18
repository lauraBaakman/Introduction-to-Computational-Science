#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grid.h"
#include "gridcontroller.h"

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
};

#endif // MAINWINDOW_H
