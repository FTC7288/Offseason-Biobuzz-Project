#pragma once

#include "jni.h"
#include <android/log.h>
#include "string"
#include <cmath>

#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, "sdk_loader", __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, "sdk_loader", __VA_ARGS__)

#define SAFE_DELETE_LOCAL(env, ref) \
    do {                            \
        LOG_INFO("Deleting -LOCAL- reference at address %p in line %d\n", (void*)ref, __LINE__); \
        if (ref != nullptr) { env->DeleteLocalRef(ref); ref = nullptr;}  \
    } while(0)

#define SAFE_DELETE_GLOBAL(env, ref) \
    do {                            \
        LOG_INFO("Deleting -GLOBAL- reference at address %p in line %d\n", (void*)ref, __LINE__); \
        if (ref != nullptr) { env->DeleteGlobalRef(ref); ref = nullptr;}  \
    } while(0)


JNIEnv* getEnv();

jclass findAndCreateGlobalRef(JNIEnv* env, const std::string& name);


namespace sdk
{
    extern JavaVM* jvm;
    extern jobject opmode;
    extern jobject hardwareMap;
    extern jmethodID getID;
}