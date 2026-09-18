#include "sdk/headers/navigation/Orientation.h"

Orientation::Orientation()
{
    JNIEnv* env = getEnv();
    orientation = env->NewObject(orientationClazz,env->GetMethodID(orientationClazz,"<init>","()V"));
}

Orientation::~Orientation()
{
    JNIEnv* env = getEnv();

    if (orientation)
    {
        SAFE_DELETE_LOCAL(env,orientation);
    }
}
