#pragma once

#include "sdk/util/Util.h"


namespace linearOpMode {

    extern jclass linearOpModeClazz;

    namespace cachedMethodIDs
    {
        extern jmethodID idleID;
        extern jmethodID terminateOpModeNowID;
        extern jmethodID waitForStartID;
        extern jmethodID opModeInInitID;
        extern jmethodID isStopRequestedID;
        extern jmethodID opModeIsActiveID;
    }

    void sleep(long millis);

    void idle();

    void terminateOpModeNow();

    void waitForStart();

    bool opModeInInit();

    bool isStopRequested();

    bool opModeIsActive();

}