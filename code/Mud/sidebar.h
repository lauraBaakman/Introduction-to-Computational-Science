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

private slots:
    void on_initApplyButton_clicked();

    void on_springBreakingMethod_currentIndexChanged(int index);

private:
    Ui::Sidebar *ui;

    Grid::Type getGridType() const;
    Grid::TypeDistribution getGridTypeDistribution() const;
    Grid::SpringBreakMethod getSpringBreakMethod() const;
    int getNumParticles() const;
    float getSpringBreakingParameter() const;

    float mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method) const;
    float mapSpringBreakingParameterToCorrectRange(int value) const;
    float mapSpringBreakingParameterToCorrectRange(Grid::SpringBreakMethod method, int value) const;

    float map(int value, float newMin, float newMax, int oldMin, int oldMax) const;
    int map(int value, int newMin, int newMax, int oldMin, int oldMax) const;

    void updateSpringBreakingMethodSlider(Grid::SpringBreakMethod method);
    void updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method, int value);
    void updateSpringBreakingMethodSliderValueLabel(Grid::SpringBreakMethod method);

    static float breakingSpringsMinMaxStrain;
    static float breakingSpringsMaxMaxStrain;
    static int breakingSpringsMinNumberOfSpringsToBreak;
    static int breakingSpringsMaxNumberOfSpringsToBreak;

    static char numberFormat;
    static int numberPrecision;
};

#endif // SIDEBAR_H
