#include "Util.h"

JNIEnv* getEnv()
{
    JNIEnv* env = nullptr;
    sdk::jvm->AttachCurrentThread(
            reinterpret_cast<JNIEnv**>(&env),
            nullptr
    );
    return env;
}

jclass findAndCreateGlobalRef(JNIEnv *env, const std::string& name)
{
    jobject localRef = env->FindClass(name.c_str());
    jobject globalRef = reinterpret_cast<jclass>(env->NewGlobalRef(localRef));
    env->DeleteLocalRef(localRef);
    return reinterpret_cast<jclass>(globalRef);
}


namespace sdk
{
    JavaVM* jvm = nullptr;
    jobject* opmode = nullptr;
    jobject hardwareMap = nullptr;
    jmethodID getID = nullptr;
}