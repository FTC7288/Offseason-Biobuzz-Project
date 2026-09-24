#include "sdk/headers/opmode/Telemetry.h"

namespace telemetry
{
    jclass telemetryClazz = nullptr;
    jobject telemetry = nullptr;

    namespace cachedMethodIDs
    {
        jmethodID updateID = nullptr;
        jmethodID addDataID = nullptr;
        jmethodID addLineID = nullptr;
    }

    bool update()
    {
        JNIEnv* env = getEnv();
        return env->CallBooleanMethod(telemetry, cachedMethodIDs::updateID);
    }


    // FIXME: Make sure to fix the issue of converting everything into a string so that data can be output properly
    void addData(const char* caption, const std::any &data)
    {
        JNIEnv* env = getEnv();
        jstring jcaption = env->NewStringUTF(caption);
        env->DeleteLocalRef(env->CallObjectMethod(telemetry, cachedMethodIDs::addDataID,jcaption,data));
        env->DeleteLocalRef(jcaption);
        env->DeleteLocalRef(jdata);
    }


    void addLine(const char* caption)
    {
        JNIEnv* env = getEnv();
        jstring jcaption = env->NewStringUTF(caption);
        env->DeleteLocalRef(env->CallObjectMethod(telemetry, cachedMethodIDs::addLineID, jcaption));
        env->DeleteLocalRef(jcaption);
    }
}