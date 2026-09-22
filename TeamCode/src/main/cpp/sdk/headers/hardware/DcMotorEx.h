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

    struct Direction
    {
        inline static jclass directionClazz = nullptr;
        inline static jobject FORWARD = nullptr;
        inline static jobject REVERSE = nullptr;
    };

    inline static jclass dcMotorExClazz = nullptr;


    explicit DcMotorEx(const char* dcMotorName, double powerTolerance);

    ~DcMotorEx();

    void setPower(double desiredMotorPower);

    void setDirection(jobject* direction) const;

    double getVelocity();

    double getCurrentPosition();

};

