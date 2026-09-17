#include "sdk/headers/navigation/Orientation.h"

Orientation::Orientation()
{
    JNIEnv* env = getEnv();
    orientation = env->NewObject(orientationClazz,env->GetMethodID(orientationClazz,"<init>","()V"));
}

Orientation::~Orientation()
{
    JNIEnv* env = getEnv();

    if (orientationClazz)
    {
        env->DeleteGlobalRef(orientationClazz);
        orientationClazz = nullptr;
    }
    if (orientation)
    {
        env->DeleteLocalRef(orientation);
        orientation = nullptr;
    }
}
