#pragma once

#include "sdk/util/util.h"

class DcMotorEx {
private:
    // Chached Method IDs
    jmethodID setPowerID = nullptr;

public:
    inline static jclass dcMotorExClazz = nullptr;
    jobject dcMotorEx = nullptr;


    explicit DcMotorEx(const char* dcMotorName);

    ~DcMotorEx();

    // Methods

    void setPower(double power) const;

};
