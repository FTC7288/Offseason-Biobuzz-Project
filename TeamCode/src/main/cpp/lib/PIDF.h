#pragma once
#include <chrono>
#include <optional>


struct PIDFCoefficents
{
public:
    double kP, kI, kD, kF, integralMax, integralMin;
    PIDFCoefficents();
    PIDFCoefficents(double kP, double kI, double kD, double kF, double integralMax, double integralMin);
};



class PIDF
{
private:
    double kP, kI, kD, kF, integralMax, integralMin, max, min;

public:

    PIDF(const PIDFCoefficents *coeffs, double max, double min);

    void setCoeffiecents(const PIDFCoefficents *coeffs, double max, double min);

    auto update(auto targetVal, auto curVal);
};

