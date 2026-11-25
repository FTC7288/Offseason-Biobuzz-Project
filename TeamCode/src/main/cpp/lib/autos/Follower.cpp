#include "Follower.h"

Follower::Follower(MecanumChassis *robotChassis, SparkFunOTOS *otos, PIDF *pidf)
    : robotChassis(robotChassis), otos(otos), pidf(pidf)
{

}

Follower::~Follower()
{

}

double Follower::cartesianToPolar(double x, double y)
{
    return std::atan2(y, x);
}

void Follower::update()
{

}

void Follower::isDone()
{

}

void Follower::followPath(const Path *path)
{

}



