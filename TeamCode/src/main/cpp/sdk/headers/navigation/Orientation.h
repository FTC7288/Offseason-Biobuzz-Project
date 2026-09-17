#pragma once

#include "sdk/util/Util.h"

struct Orientation
{
public:
    inline static jclass orientationClazz = nullptr;

    jobject orientation = nullptr;

    float firstAngle = 0;
    float secondAngle = 0;
    float thirdAngle = 0;
};
