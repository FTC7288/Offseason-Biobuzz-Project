#include "sdk/sdk.h"

using namespace linearOpMode;

extern "C" void Test(JNIEnv* env, jobject thiz)
{
    sdk::opmode=&thiz;
    initSDK(env);

    LOG_INFO("Running from c++");
    LOG_ERROR("HI");

    waitForStart();

    while (opModeIsActive()) {}

}

TeleOp(Test, GROUP2)