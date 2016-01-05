#include "sidebar.h"
#include "ui_sidebar.h"

float Sidebar::breakingSpringsMinMaxStrain = 0.1;
float Sidebar::breakingSpringsMaxMaxStrain = 5.0;

int Sidebar::breakingSpringsMinNumberOfSpringsToBreak = 1;
int Sidebar::breakingSpringsMaxNumberOfSpringsToBreak;

char Sidebar::numberFormat = 'f';
int Sidebar::numberPrecision = 2;

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
    //Set the max value of the slider if we are setting number of springs to break to the total number of particles.
    Sidebar::breakingSpringsMaxNumberOfSpringsToBreak = ui->horizontalSlider->value() * 4;
    updateSpringBreakingMethodSlider();
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
    return mapSpringBreakingParameterToCorrectRange();
}

float Sidebar::mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method) const
{
    return mapSpringBreakingParameterToCorrectRange(method, ui->breakingSpringsParameterSlider->value());
}

float Sidebar::mapSpringBreakingParameterToCorrectRange(int value) const
{
    return mapSpringBreakingParameterToCorrectRange(getSpringBreakMethod(), value);
}

float Sidebar::mapSpringBreakingParameterToCorrectRange() const
{
    return mapSpringBreakingParameterToCorrectRange(getSpringBreakMethod());
}

float Sidebar::mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method, int value) const
{
    int sliderMin = ui->breakingSpringsParameterSlider->minimum();
    int sliderMax = ui->breakingSpringsParameterSlider->maximum();
    float mappedValue;
    switch(method){
    case Grid::X_SPRINGS_WITH_HIGHEST_STRAIN:
        mappedValue = map(value,
                         breakingSpringsMinNumberOfSpringsToBreak, breakingSpringsMaxNumberOfSpringsToBreak,
                         sliderMin, sliderMax);
        break;
    case Grid::SPRINGS_WITH_STRAIN_GREATER_THAN:
        mappedValue = map(value,
                         breakingSpringsMinMaxStrain, breakingSpringsMaxMaxStrain,
                         sliderMin, sliderMax);
        break;
    }
    return mappedValue;
}

float Sidebar::map(int value, float newMin, float newMax, int oldMin, int oldMax) const
{
    float newRange = newMax - newMin;
    float oldRange = static_cast<float>(oldMax - oldMin);

    float scaledValue = (static_cast<float>(value) - oldMin) / oldRange;

    return newMin + (scaledValue * newRange);
}

int Sidebar::map(int value, int newMin, int newMax, int oldMin, int oldMax) const
{
    int newRange = newMax - newMin;
    float oldRange = static_cast<float>(oldMax - oldMin);

    float scaledValue = (static_cast<float>(value - oldMin)) / oldRange;

    return newMin + (scaledValue * newRange);
}

void Sidebar::updateSpringBreakingMethodSlider(Grid::SpringBreakMethod method)
{
    QString minLabel;
    QString maxLabel;

    switch(method){
    case Grid::X_SPRINGS_WITH_HIGHEST_STRAIN:
        qDebug() << "Update slider: X_SPRINGS_WITH_HIGHEST_STRAIN";
        minLabel.setNum(breakingSpringsMinNumberOfSpringsToBreak);
        maxLabel.setNum(breakingSpringsMaxNumberOfSpringsToBreak);
        break;
    case Grid::SPRINGS_WITH_STRAIN_GREATER_THAN:
        qDebug() << "Update slider: SPRINGS_WITH_STRAIN_GREATER_THAN";
        minLabel.setNum(breakingSpringsMinMaxStrain, numberFormat, numberPrecision);
        maxLabel.setNum(breakingSpringsMaxMaxStrain, numberFormat, numberPrecision);
        break;
    }
    ui->breakingSpringsMin->setText(minLabel);
    ui->breakingSpringsMax->setText(maxLabel);
    updateSpringBreakingMethodSliderValueLabel(method);
}

void Sidebar::updateSpringBreakingMethodSlider()
{
    updateSpringBreakingMethodSlider(getSpringBreakMethod());
}

void Sidebar::updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method, int value)
{
    float mappedValue = mapSpringBreakingParameterToCorrectRange(method, static_cast<float>(value));
    QString label;

    switch(method){
    case Grid::X_SPRINGS_WITH_HIGHEST_STRAIN:
        label.setNum(static_cast<int>(mappedValue));
        break;
    case Grid::SPRINGS_WITH_STRAIN_GREATER_THAN:
        label.setNum(mappedValue, numberFormat, numberPrecision);
        break;
    }
    ui->breakingSpringsValue->setText(label);
}

void Sidebar::updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method)
{
    int value = ui->breakingSpringsParameterSlider->value();
    updateSpringBreakingMethodSliderValueLabel(method, value);
}

void Sidebar::updateSpringBreakingMethodSliderValueLabel(int value)
{
    Grid::SpringBreakMethod method = getSpringBreakMethod();
    updateSpringBreakingMethodSliderValueLabel(method, value);
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

void Sidebar::on_springBreakingMethod_currentIndexChanged(int index)
{
    updateSpringBreakingMethodSlider(static_cast<Grid::SpringBreakMethod>(index));
}

void Sidebar::on_breakingSpringsParameterSlider_sliderMoved(int position)
{
    updateSpringBreakingMethodSliderValueLabel(position);
}
