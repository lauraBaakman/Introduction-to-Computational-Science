#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
}

Sidebar::~Sidebar()
{
    delete ui;
}

Grid::Type Sidebar::getGridType() const
{
    return static_cast<Grid::Type>(ui->gridType->currentIndex());
}

Grid::TypeDistribution Sidebar::getGridTypeDistribution() const
{
    return static_cast<Grid::TypeDistribution>(
                ui->gridTypeDistribution->currentIndex());
}

void Sidebar::on_initApplyButton_clicked()
{
    Grid::Settings settings;
    settings.type = getGridType();
    settings.typeDistribution = getGridTypeDistribution();
//  settings.width = iets;
//  setting.height = ietsanders;
    emit replaceGridSignal(settings);
}
