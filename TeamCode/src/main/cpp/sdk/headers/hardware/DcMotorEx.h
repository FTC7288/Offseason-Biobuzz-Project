#pragma once

#include "sdk/util/Util.h"

class DcMotorEx
{
private:
    const char* dcMotorName = nullptr;
    jobject dcMotorEx = nullptr;

    jmethodID setPowerID = nullptr;
    jmethodID setDirectionID = nullptr;
    jmethodID getVelocityID = nullptr;
    jmethodID getCurrentPositionID = nullptr;
    double motorPowerTolerance = 0;
    double currentMotorPower = 0;

public:
    enum class Direction
    {
        FORWARD,
        REVERSE
    };

    inline static jclass dcMotorExClazz = nullptr;
    inline static jclass directionClazz = nullptr;


    explicit DcMotorEx(const char* dcMotorName, double powerTolerance);

    ~DcMotorEx();

    void setPower(double desiredMotorPower);

    void setDirection(const Direction& direction) const;

    double getVelocity();

    double getCurrentPosition();

};
