#pragma once

#include "jni.h"

#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, "sdk_loader", __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, "sdk_loader", __VA_ARGS__)

namespace sdk
{
    extern JavaVM* jvm;
    extern JNIEnv* env;
    extern jobject thiz;
}