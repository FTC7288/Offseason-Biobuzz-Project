//
// Created by Sam on 11/17/2026.
//

#include "Path.h"

Path::Path(std::convertible_to<Pose2D> auto&&... points)
{
    this->points.reserve(sizeof...(points));
    (this->points.push_back(std::make_unique<Pose2D>(std::forward<decltype(points)>(points))), ...);
}
