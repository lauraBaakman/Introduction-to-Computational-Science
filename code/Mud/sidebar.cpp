#include "sidebar.h"
#include "ui_sidebar.h"

float Sidebar::breakingSpringsMinMaxStrain = 0.1;
float Sidebar::breakingSpringsMaxMaxStrain = 5.0;
int Sidebar::breakingSpringsMinNumberOfSpringsToBreak = 1;
int Sidebar::breakingSpringsMaxNumberOfSpringsToBreak;

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
    Sidebar::breakingSpringsMaxNumberOfSpringsToBreak = ui->horizontalSlider->value();
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

Grid::SpringBreakMethod Sidebar::getSpringBreakMethod() const
{
    return static_cast<Grid::SpringBreakMethod>(
                ui->springBreakingMethod->currentIndex());
}

int Sidebar::getNumParticles() const
{
    return ui->horizontalSlider->value();
}

float Sidebar::getSpringBreakingParameter() const
{
    int value = ui->breakingSpringsParameterSlider->value();
    return static_cast<float>(value);
}

void Sidebar::on_initApplyButton_clicked()
{
    emit replaceGridSignal(getGridSettings());
}

Grid::Settings Sidebar::getGridSettings()
{
    Grid::Settings settings;
    settings.type = getGridType();
    settings.typeDistribution = getGridTypeDistribution();
    settings.numParticles = getNumParticles();
    settings.springBreakMethod = getSpringBreakMethod();
    settings.springBreakParameter = getSpringBreakingParameter();
    return settings;
}
