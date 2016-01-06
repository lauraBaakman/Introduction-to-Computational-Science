#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

#include <c++/v1/map>

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

    Grid::Settings getGridSettings();

signals:
    void replaceGridSignal(Grid::Settings settings);
    void doBreak();
    void doSolve();

private slots:
    void on_initApplyButton_clicked();

    void on_springBreakingMethod_currentIndexChanged(int index);

    void on_breakingSpringsParameterSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderPressed();

    void on_breakingSpringsParameterSlider_valueChanged(int value);

    void on_simulateStepButton_clicked();

    void on_doStabilizeButton_clicked();

private:
    Ui::Sidebar *ui;

    Grid::Type getGridType() const;
    Grid::TypeDistribution getGridTypeDistribution() const;
    Grid::SpringBreakMethod getSpringBreakMethod() const;
    int getNumParticles() const;
    float getSpringBreakingParameter() const;

    float mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method) const;
    float mapSpringBreakingParameterToCorrectRange(int value) const;
    float mapSpringBreakingParameterToCorrectRange() const;
    float mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method, int value) const;

    float map(int value, float newMin, float newMax, int oldMin, int oldMax) const;
    int map(int value, int newMin, int newMax, int oldMin, int oldMax) const;

    void updateSpringBreakingMethodSlider(Grid::SpringBreakMethod method);
    void updateSpringBreakingMethodSlider();

    void updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method, int value);
    void updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method);
    void updateSpringBreakingMethodSliderValueLabel(int value);

    void updateMaxNumSpringsToBreak(int numberOfParticles);

    static float breakingSpringsMinMaxStrain;
    static float breakingSpringsMaxMaxStrain;
    static int breakingSpringsMinNumberOfSpringsToBreak;
    static int breakingSpringsMaxNumberOfSpringsToBreak;

    static char numberFormat;
    static int numberPrecision;
};

#endif // SIDEBAR_H
