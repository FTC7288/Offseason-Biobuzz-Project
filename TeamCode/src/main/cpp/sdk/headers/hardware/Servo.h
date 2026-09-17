#pragma once

#include "sdk/util/Util.h"

class Servo {
private:
    jobject servo = nullptr;

    jmethodID setPositionID = nullptr;
    double servoPositionTolerance = 0;
    double currentServoPosition = 0;

public:

    inline static jclass servoClazz = nullptr;

    explicit Servo(const char* servoName, double positionTolerance);

    ~Servo();

    void setPosition(double desiredPosition);


};
