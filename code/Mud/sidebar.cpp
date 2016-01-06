#include "sidebar.h"
#include "ui_sidebar.h"

float Sidebar::breakingSpringsMinMaxStrain = 0.1;
float Sidebar::breakingSpringsMaxMaxStrain = 5.0;

int Sidebar::breakingSpringsMinNumberOfSpringsToBreak = 1;
int Sidebar::breakingSpringsMaxNumberOfSpringsToBreak;

QPair<double, double> Sidebar::springConstantMeanMinMax = QPair<double, double>(0.0, 5.0);
QPair<double, double> Sidebar::springConstantStdMinMax = QPair<double, double>(0.0, 2.0);

char Sidebar::numberFormat = 'f';
int Sidebar::numberPrecision = 2;

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
    //Set the max value of the slider if we are setting number of springs to break to the total number of particles.
    updateMaxNumSpringsToBreak(ui->horizontalSlider->value());
    on_springConstantStandardDeviation_valueChanged(ui->springConstantStandardDeviation->value());
    on_springConstantMean_valueChanged(ui->springConstantMean->value());
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

double Sidebar::getSpringConstantMean() const
{
    int value = ui->springConstantMean->value();
    double mappedValue = map(value,
                             springConstantMeanMinMax,
                             ui->springConstantMean->minimum(), ui->springConstantMean->maximum());
    return mappedValue;
}

double Sidebar::getSpringConstantSD() const
{
    int value = ui->springConstantStandardDeviation->value();
    double mappedValue = map(value,
                             springConstantStdMinMax,
                             ui->springConstantStandardDeviation->minimum(), ui->springConstantStandardDeviation->maximum());
    return mappedValue;
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

double Sidebar::map(int value, double newMin, double newMax, int oldMin, int oldMax) const
{
    double newRange = newMax - newMin;
    double oldRange = (static_cast<double>(oldMax - oldMin));

    double scaledValue = (static_cast<double>(value - oldMin)) / oldRange;

    return newMin + (scaledValue * newRange);
}

double Sidebar::map(int value, QPair<double, double> newMinMax, int oldMin, int oldMax) const
{
    return map(value, newMinMax.first, newMinMax.second, oldMin, oldMax);
}

void Sidebar::updateSpringBreakingMethodSlider(Grid::SpringBreakMethod method)
{
    QString minLabel;
    QString maxLabel;

    switch(method){
    case Grid::X_SPRINGS_WITH_HIGHEST_STRAIN:
        minLabel.setNum(breakingSpringsMinNumberOfSpringsToBreak);
        maxLabel.setNum(breakingSpringsMaxNumberOfSpringsToBreak);
        break;
    case Grid::SPRINGS_WITH_STRAIN_GREATER_THAN:
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

void Sidebar::updateMaxNumSpringsToBreak(int numberOfParticles)
{
    Sidebar::breakingSpringsMaxNumberOfSpringsToBreak = numberOfParticles * 4;
    updateSpringBreakingMethodSlider();
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
    settings.springConstantmean = getSpringConstantMean();
    settings.springConstantSD = getSpringConstantSD();
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

void Sidebar::on_horizontalSlider_sliderMoved(int position)
{
    updateMaxNumSpringsToBreak(position);
}

void Sidebar::on_horizontalSlider_sliderPressed()
{
    updateMaxNumSpringsToBreak(ui->horizontalSlider->value());
}

void Sidebar::on_breakingSpringsParameterSlider_valueChanged(int value)
{
    updateSpringBreakingMethodSliderValueLabel(value);
}

void Sidebar::on_simulateStepButton_clicked()
{
    emit doBreak();
}

void Sidebar::on_doStabilizeButton_clicked()
{
    emit doSolve();
}

void Sidebar::on_springConstantStandardDeviation_valueChanged(int value)
{
    QString label;
    double mappedValue = getSpringConstantSD();
    ui->SpringConstantStandardDeviationValue->setText(label.setNum(mappedValue, numberFormat, numberPrecision));
}

void Sidebar::on_springConstantMean_valueChanged(int value)
{
    QString label;
    double mappedValue = getSpringConstantMean();
    ui->springConstantMeanLabel->setText(label.setNum(mappedValue, numberFormat, numberPrecision));
}
