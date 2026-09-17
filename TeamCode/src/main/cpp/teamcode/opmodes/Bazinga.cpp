#include "sdk/Sdk.h"

using namespace linearOpMode;
using namespace gamepads;


extern "C" void Bazinga(JNIEnv* env, jobject thiz)
{
    initSDK(env, &thiz);

    std::unique_ptr<DcMotorEx> lift = std::make_unique<DcMotorEx>("lift", 0.01);
    std::unique_ptr<DcMotorEx> left = std::make_unique<DcMotorEx>("left",0.01);
    std::unique_ptr<DcMotorEx> right = std::make_unique<DcMotorEx>("right",0.01);
    right->setDirection(DcMotorEx::Direction::REVERSE);

    std::unique_ptr<Servo> spin = std::make_unique<Servo>("spin", 0.01);

    std::unique_ptr<LynxModule> controlHub = std::make_unique<LynxModule>("Control Hub");
    controlHub->setBulkCachingMode(LynxModule::BulkCachingMode::AUTO);




    waitForStart();

    LOG_INFO("HELLO FROM C++");
    LOG_INFO("THIS IS EPIC");


    while (opModeIsActive()) {


        telemetry::update();
        gamepads::update();

        telemetry::addLine("BINGO BANGO SHBOINGO");


        left->setPower(gamepad1->left_stick_y);
        right->setPower(gamepad1->right_stick_y);

        int liftDirection = (gamepad1->dpad_down) ? -1 : 1;
        lift->setPower((gamepad1->dpad_down || gamepad1->dpad_up) ? liftDirection * .5 : 0);


        spin->setPosition(gamepad1->right_trigger);


        double number = 10;
        telemetry::addData("NUMBER: ", std::to_string(number).c_str());
        telemetry::addData("Trigger Pressed? : ", std::to_string(gamepad1->leftTriggerDown()).c_str());

    }
}

TeleOp(Bazinga, SIX_SEVEN_MANGO_MUSTARD)