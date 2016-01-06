#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Obviously setting up the UI
    ui->setupUi(this);

    // Need to create a new grid as specified by the default ui settings.
    this->grid = new Grid();
    this->grid->gridFactory(ui->sidebar->getGridSettings());

    // Create the solver with the pointer to the grid
    GridSolver *gridSolver = new GridSolver(grid);

    // Add solver and model (grid) pointer to the controller
    this->gridController = new GridController(grid, gridSolver, this->ui->canvas);

    // Setup connections between sidebar and the grid controller
    QObject::connect(ui->sidebar, SIGNAL(replaceGridSignal(Grid::Settings)),
                     this->gridController, SLOT(replaceGridSlot(Grid::Settings)));

    QObject::connect(ui->sidebar, SIGNAL(doBreak()),
                     this->gridController, SLOT(doBreak()));

    QObject::connect(ui->sidebar, SIGNAL(doSolve()),
                     this->gridController, SLOT(doSolve()));


}

MainWindow::~MainWindow()
{
    delete ui;

    delete grid;
    delete gridSolver;
    delete gridController;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}
