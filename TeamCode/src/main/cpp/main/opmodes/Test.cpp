#include "sdk/sdk.h"

extern "C" void Test(JNIEnv* env, jobject thiz)
{
    LOG_INFO("Running from c++");
    LOG_ERROR("HI");
}

Autonomous(Test)