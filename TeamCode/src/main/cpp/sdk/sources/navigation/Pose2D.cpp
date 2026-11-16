#include "sdk/headers/navigation/Pose2D.h"


Pose2D::Pose2D(double x, double y, double h)
{
    this->x = x;
    this->y = y;
    this->h = h;
}

Pose2D::Pose2D()
{
    this->x = 0;
    this->y = 0;
    this->h = 0;
}
