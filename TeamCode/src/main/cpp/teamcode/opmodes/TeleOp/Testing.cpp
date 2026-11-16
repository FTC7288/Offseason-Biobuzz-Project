#include "sdk/Sdk.h"
#include "lib/CustomLib.h"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void Testing(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);

    DcMotorEx lift {"lift", 0};
    lift.setZeroPowerMode(&DcMotorEx::ZeroPowerMode::FLOAT);

    LynxModule controlHub = LynxModule("Control Hub");

    waitForStart();

    while (opModeIsActive())
    {
        gamepads::update();
        telemetry::update();

        telemetry::addData("Left Stick X", std::to_string(gamepad1->left_stick_x).c_str());
        telemetry::addData("Left Stick Y", std::to_string(gamepad1->left_stick_y).c_str());
        telemetry::addData("Right Stick X", std::to_string(gamepad1->right_stick_x).c_str());
        telemetry::addData("Right Stick Y", std::to_string(gamepad1->right_stick_y).c_str());
    }
}

TeleOp(Testing, dummy)
