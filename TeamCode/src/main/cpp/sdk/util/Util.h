#pragma once

#include "jni.h"
#include <android/log.h>
#include "string"
#include <cmath>
#include <vector>

#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, "sdk_loader", __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, "sdk_loader", __VA_ARGS__)


#define SAFE_DELETE_LOCAL(env, ref) \
    do {                            \
        LOG_INFO("Deleting -LOCAL- reference at address -%p- in line -%d- in file -%s-\n", (void*)ref, __LINE__, __FILE__); \
        if (ref != nullptr) { env->DeleteLocalRef(ref); ref = nullptr;}  \
    } while(0)

#define SAFE_DELETE_GLOBAL(env, ref, LINE, FILE) \
    do {                            \
        LOG_INFO("Deleting -GLOBAL- reference at address -%p- in line -%d- in file -%s-\n", (void*)ref, LINE, FILE); \
        if (ref != nullptr) { env->DeleteGlobalRef(ref); ref = nullptr;}  \
    } while(0)



struct GlobalReference
{
public:
    jobject ref;
    int LINE;
    const char* FILE;
};


namespace GLOBAL_REFS
{
    extern std::vector<GlobalReference> gRefArray;
}

namespace sdk
{
    extern JavaVM* jvm;
    extern jobject opmode;
    extern jobject hardwareMap;
    extern jmethodID getID;
}

JNIEnv* getEnv();

jclass findAndCreateGlobalRef(JNIEnv* env, const std::string& name, int LINE, const char* FILE);

jobject findAndCreateGlobalEnumRef(JNIEnv *env, jclass *clazz, const char *name, const char *signature, int LINE, const char* FILE);


