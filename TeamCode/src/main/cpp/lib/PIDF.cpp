#include "PIDF.h"

using namespace std::chrono;

PIDFCoefficents::PIDFCoefficents(double kP, double kI, double kD, double kF, double integralMax, double integralMin)
{
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->kF = kF;
    this->integralMax = integralMax;
    this->integralMin = integralMin;
}

PIDFCoefficents::PIDFCoefficents()
{
    this->kP = 0;
    this->kI = 0;
    this->kD = 0;
    this->kF = 0;
    this->integralMax = 0;
    this->integralMin = 0;
}



PIDF::PIDF(const PIDFCoefficents *coeffs, double max, double min)
{
    this->kP = coeffs->kP;
    this->kI = coeffs->kI;
    this->kD = coeffs->kD;
    this->kF = coeffs->kF;
    this->integralMax = coeffs->integralMax;
    this->integralMin = coeffs->integralMin;
    this->max = max;
    this->min = min;
}


void PIDF::setCoeffiecents(const PIDFCoefficents *coeffs, double max, double min)
{
    this->kP = coeffs->kP;
    this->kI = coeffs->kI;
    this->kD = coeffs->kD;
    this->kF = coeffs->kF;
    this->integralMax = coeffs->integralMax;
    this->integralMin = coeffs->integralMin;
    this->max = max;
    this->min = min;
}


auto PIDF::update(auto targetVal, auto curVal)
{
    static double previousError;
    static double previousTimeStep;
    static double integral;

    auto time = steady_clock::now();
    double curTimeStep = duration<double,std::milli>(time.time_since_epoch()).count();

    double dt = curTimeStep - previousTimeStep;
    double error = targetVal - curVal;

    integral += error * dt;
    if (integral > integralMax)
    {
        integral = integralMax;
    } else if (integral < integralMin)
    {
        integral = integralMin;
    }

    double P = kP * error;
    double I = kI * integral;
    double D = kD * (error - previousError) / dt;

    curVal += P + I + D + kF;
    previousError = error;
    previousTimeStep = curTimeStep;
    return curVal;
}

