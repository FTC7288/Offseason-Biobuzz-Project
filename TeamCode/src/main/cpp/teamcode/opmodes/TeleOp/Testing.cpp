#include "sdk/Sdk.h"
#include "lib/CustomLib.h"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void Testing(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);

    double frPos = 0.98;
    double flPos = 0.02;
    Servo flowerLeft {"flowerLeft", 0};
    Servo flowerRight {"flowerRight", 0};

    LynxModule controlHub = LynxModule("Control Hub");

    waitForStart();

    while (opModeIsActive()) {
        gamepads::update();
        telemetry::update();

        telemetry::addData("Left Stick X", std::to_string(gamepad1->left_stick_x).c_str());
        telemetry::addData("Left Stick Y", std::to_string(gamepad1->left_stick_y).c_str());
        telemetry::addData("Right Stick X", std::to_string(gamepad1->right_stick_x).c_str());
        telemetry::addData("Right Stick Y", std::to_string(gamepad1->right_stick_y).c_str());

        if (gamepad1->dpad_down) {
            flPos += 0.001;
            frPos -= 0.001;
        } else if (gamepad1->dpad_up) {
            flPos -= 0.001;
            frPos += 0.001;
        }

        flowerLeft.setPosition(flPos);
        flowerRight.setPosition(frPos);
        telemetry::addData("Right Servo", std::to_string(frPos).c_str());
        telemetry::addData("Left Servo", std::to_string(flPos).c_str());


    }
}

TeleOp(Testing, dummy)
