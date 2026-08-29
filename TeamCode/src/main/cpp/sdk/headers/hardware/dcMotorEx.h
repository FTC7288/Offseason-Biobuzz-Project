#pragma once

#include "sdk/util/util.h"

class DcMotorEx {
private:
    jmethodID setPowerID = nullptr;

public:
    enum class Direction
    {
        FORWARD,
        REVERSE
    };

    inline static jclass dcMotorExClazz = nullptr;
    inline static jclass directionClazz = nullptr;

    jobject dcMotorEx = nullptr;


    explicit DcMotorEx(const char* dcMotorName);

    ~DcMotorEx();

    // Methods

    void setPower(double power) const;

    void setDirection(const Direction& direction) const;

};
