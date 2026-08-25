#include "sdk/sdk.h"

extern "C" void Test()
{
    LOG_INFO("Running from c++");
    LOG_ERROR("HI");
}

Autonomous(Test)