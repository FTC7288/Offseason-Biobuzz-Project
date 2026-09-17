#pragma once

#include "jni.h"
#include <android/log.h>
#include "string"
#include <cmath>

#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, "sdk_loader", __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, "sdk_loader", __VA_ARGS__)

JNIEnv* getEnv();

jclass findAndCreateGlobalRef(JNIEnv* env, const std::string& name);


namespace sdk
{
    extern JavaVM* jvm;
    extern jobject* opmode;
    extern jobject hardwareMap;
    extern jmethodID getID;
}