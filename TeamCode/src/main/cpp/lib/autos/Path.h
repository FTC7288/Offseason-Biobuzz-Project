#pragma once

#include <utility>
#include "sdk/headers/navigation/Pose2D.h"



struct Path
{
public:
    explicit Path(std::convertible_to<Pose2D> auto&&... points);

    std::vector<std::unique_ptr<Pose2D>> points;
};

