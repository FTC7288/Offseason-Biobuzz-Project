#include "sdk/sdk.h"

using namespace linearOpMode;


extern "C" void Bazinga(JNIEnv* env, jobject thiz)
{
    sdk::opmode=&thiz;
    initSDK(env);


    waitForStart();

    LOG_INFO("HELLO FROM C++");
    LOG_INFO("THIS IS EPIC");


    while (opModeIsActive()) {
        telemetry::update();
        gamepads::update();

        telemetry::addLine("BINGO BANGO SHBOINGO");

        double number = 10;
        telemetry::addData("NUMBER: ", std::to_string(number).c_str());
        telemetry::addData("Trigger Pressed? : ", std::to_string(gamepads::gamepad1->leftTriggerDown()).c_str());

    }

}

Autonomous(Bazinga)