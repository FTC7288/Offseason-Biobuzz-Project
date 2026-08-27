#include "sdk/sdk.h"

using namespace linearOpMode;
using namespace gamepads;


extern "C" void Bazinga(JNIEnv* env, jobject thiz)
{
    sdk::opmode=&thiz;
    initSDK(env);

    std::unique_ptr<DcMotorEx> lift = std::make_unique<DcMotorEx>("lift");
    std::unique_ptr<DcMotorEx> left = std::make_unique<DcMotorEx>("left");
    std::unique_ptr<DcMotorEx> right = std::make_unique<DcMotorEx>("right");


    waitForStart();

    LOG_INFO("HELLO FROM C++");
    LOG_INFO("THIS IS EPIC");


    while (opModeIsActive()) {
        telemetry::update();
        gamepads::update();

        telemetry::addLine("BINGO BANGO SHBOINGO");


        left->setPower(gamepad1->left_stick_y);
        right->setPower(-gamepad1->right_stick_y);

        int liftDirection = (gamepad1->dpad_down) ? -1 : 1;
        lift->setPower((gamepad1->dpad_down || gamepad1->dpad_up) ? liftDirection * .5 : 0);




        double number = 10;
        telemetry::addData("NUMBER: ", std::to_string(number).c_str());
        telemetry::addData("Trigger Pressed? : ", std::to_string(gamepad1->leftTriggerDown()).c_str());

    }
}

TeleOp(Bazinga)