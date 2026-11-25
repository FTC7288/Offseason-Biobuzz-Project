#pragma once
#include "sdk/Sdk.h"
#include "lib/MecanumChassis.h"
#include "lib/PIDF.h"
#include "Path.h"

class Follower
{
private:

    MecanumChassis* robotChassis = nullptr;
    SparkFunOTOS* otos = nullptr;
    PIDF* pidf = nullptr;

    double x, y, h, t, dt;

    double cartesianToPolar(double x, double y);

public:

    Follower(MecanumChassis* robotChassis, SparkFunOTOS* otos, PIDF* pidf);
    ~Follower();

    void update();

    void isDone();

    void followPath(const Path *path);
};

