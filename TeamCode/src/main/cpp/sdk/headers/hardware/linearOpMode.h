#pragma once

#include "../../util/util.h"


namespace linearOpMode {

    void sleep();

    void idle();

    void terminateOpModeNow();

    void waitForStart();

    bool opModeInInit();

    bool isStopRequested();

    bool opModeIsActive();

    double getRuntime();
}