#pragma once

//SOFTWARE INCLUDES
#include <jni.h>
#include <android/log.h>
#include <memory>
#include <string_view>
#include <string>
#include <thread>

#include "sdk/util/util.h"
#include "sdk/util/opmodeRegistry.h"
#include "sdk/util/initSDK.h"

#include "sdk/headers/opmode/linearOpMode.h"
#include "sdk/headers/opmode/telemetry.h"


//HARDWARE INCLUDES
#include "sdk/headers/hardware/dcMotorEx.h"
#include "sdk/headers/hardware/gamepad.h"
