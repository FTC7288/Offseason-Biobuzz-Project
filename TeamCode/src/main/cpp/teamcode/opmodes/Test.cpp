#include "sdk/Sdk.h"

using namespace linearOpMode;

extern "C" void Test(JNIEnv* env, jobject thiz)
{
    initSDK(env, &thiz);

    LOG_INFO("Running from c++");
    LOG_ERROR("HI");

    waitForStart();

    while (opModeIsActive()) {}

}

TeleOp(Test, GROUP2)