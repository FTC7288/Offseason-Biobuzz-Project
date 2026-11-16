#pragma once

#include "sdk/util/Util.h"

class Pose2D {
public:
    jobject pose2D = nullptr;

    inline static jclass pose2DClazz = nullptr;

    Pose2D();
    Pose2D(double x, double y, double h);

    double x;
    double y;
    double h;
};

