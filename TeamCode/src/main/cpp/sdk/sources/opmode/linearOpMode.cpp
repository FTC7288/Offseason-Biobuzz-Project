//
// Created by samin on 8/23/2026.
//

#include "sdk/headers/opmode/linearOpMode.h"

namespace linearOpMode {

    jclass linearOpModeClazz = nullptr;

    namespace cachedMethodIDs
    {
        jmethodID idleID = nullptr;
        jmethodID terminateOpModeNowID = nullptr;
        jmethodID waitForStartID = nullptr;
        jmethodID opModeInInitID = nullptr;
        jmethodID isStopRequestedID = nullptr;
        jmethodID opModeIsActiveID = nullptr;
    }

    // TODO: Make this sleep function safe to use during operation as it will still terminate and cause a error each time its stopped mid sleep
    void sleep(long milliseconds) {
        JNIEnv* env = getEnv();
        jclass sleepClazz = env->FindClass("java/lang/Thread");
        jmethodID sleepMid = env->GetStaticMethodID(sleepClazz, "sleep", "(J)V");
        env->CallStaticVoidMethod(sleepClazz, sleepMid, (jlong)milliseconds);
    }

    void idle()
    {
        JNIEnv* env = getEnv();
        env->CallVoidMethod(*sdk::opmode,cachedMethodIDs::idleID);
    }

    void terminateOpModeNow()
    {
        JNIEnv* env = getEnv();
        env->CallVoidMethod(*sdk::opmode,cachedMethodIDs::terminateOpModeNowID);
    }

    void waitForStart()
    {
        JNIEnv* env = getEnv();
        env->CallVoidMethod(*sdk::opmode,cachedMethodIDs::waitForStartID);
    }

    bool opModeInInit()
    {
        JNIEnv* env = getEnv();
        return env->CallBooleanMethod(*sdk::opmode,cachedMethodIDs::opModeInInitID);
    }

    bool isStopRequested()
    {
        JNIEnv* env = getEnv();
        return env->CallBooleanMethod(*sdk::opmode,cachedMethodIDs::isStopRequestedID);
    }

    bool opModeIsActive()
    {
        JNIEnv* env = getEnv();
        return env->CallBooleanMethod(*sdk::opmode,cachedMethodIDs::opModeIsActiveID);
    }
}