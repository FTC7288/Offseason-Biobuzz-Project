#include "Util.h"

namespace GLOBAL_REFS
{
    std::vector<GlobalReference> gRefArray = {};
}

JNIEnv* getEnv()
{
    JNIEnv* env = nullptr;
    sdk::jvm->AttachCurrentThread(
            reinterpret_cast<JNIEnv**>(&env),
            nullptr
    );
    return env;
}


jclass findAndCreateGlobalRef(JNIEnv *env, const std::string& name, int LINE, const char* FILE)
{
    jobject localRef = env->FindClass(name.c_str());
    jobject globalRef = reinterpret_cast<jclass>(env->NewGlobalRef(localRef));
    env->DeleteLocalRef(localRef);
    jclass clazz = reinterpret_cast<jclass>(globalRef);
    GLOBAL_REFS::gRefArray.push_back({clazz,LINE,FILE});
    return clazz;
}

jobject findAndCreateGlobalEnumRef(JNIEnv *env, jclass *clazz, const char *name, const char *signature, int LINE, const char* FILE)
{
    jobject globalRef = env->NewGlobalRef(env->GetStaticObjectField(*clazz, env->GetStaticFieldID(*clazz, name,signature)));
    GLOBAL_REFS::gRefArray.push_back({globalRef,LINE,FILE});
    return globalRef;
}


namespace sdk
{
    JavaVM* jvm = nullptr;
    jobject opmode = nullptr;
    jobject hardwareMap = nullptr;
    jmethodID getID = nullptr;
}