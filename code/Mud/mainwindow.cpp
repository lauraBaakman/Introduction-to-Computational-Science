#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->grid = new Grid();
    this->grid->gridFactory(ui->sidebar->getGridSettings());

    GridSolver *gridSolver = new GridSolver(grid);
    this->gridController = new GridController(grid, gridSolver, this->ui->canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}
