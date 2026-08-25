#include "sdk/sdk.h"

extern "C" void Bazinga()
{
    LOG_INFO("HELLO FROM C++");
    LOG_INFO("THIS IS EPIC");
}

Autonomous(Bazinga)