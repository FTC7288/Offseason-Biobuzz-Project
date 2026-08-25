//
// Created by samin on 8/23/2026.
//

#include "sdk/headers/software/linearOpMode.h"

namespace linearOpMode {

    jclass cur_clazz;

    jobject cur_thiz;

    void sleep()
    {
        sdk::env->CallVoidMethod(thiz,sdk::env->GetMethodID(cur_clazz, "waitForStart", "()V"));
    }

    void idle()
    {
        sdk::env->CallVoidMethod(thiz,sdk::env->GetMethodID(cur_clazz, "idle", "()V"));
    }

    void terminateOpModeNow()
    {
        sdk::env->CallVoidMethod(thiz,sdk::env->GetMethodID(cur_clazz, "terminateOpModeNow", "()V"));
    }

    void waitForStart()
    {
        sdk::env->CallVoidMethod(thiz,sdk::env->GetMethodID(cur_clazz, "waitForStart", "()V"));
    }

    bool opModeInInit()
    {
        return sdk::env->CallBooleanMethod(thiz,sdk::env->GetMethodID(cur_clazz, "opModeInInit", "()Z"));
    }

    bool isStopRequested()
    {
        return sdk::env->CallBooleanMethod(thiz,sdk::env->GetMethodID(cur_clazz, "isStopRequested", "()Z"));
    }

    bool opModeIsActive()
    {
        return sdk::env->CallBooleanMethod(thiz,sdk::env->GetMethodID(cur_clazz, "opModeIsActive", "()Z"));
    }

    double getRuntime()
    {
        return sdk::env->CallDoubleMethod(thiz,sdk::env->GetMethodID(cur_clazz, "getRuntime", "()D"));
    }
}