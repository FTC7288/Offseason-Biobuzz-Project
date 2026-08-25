#pragma once

#include "sdk/util/util.h"


namespace linearOpMode {

    extern jclass clazz;

    extern jobject thiz;

    void sleep();

    void idle();

    void terminateOpModeNow();

    void waitForStart();

    bool opModeInInit();

    bool isStopRequested();

    bool opModeIsActive();

    double getRuntime();
}