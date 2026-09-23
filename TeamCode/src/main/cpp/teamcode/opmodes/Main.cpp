#include "sdk/Sdk.h"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void Main (JNIEnv *env, jobject thiz)
{
    initSDK(env, thiz);


    const double motorPowerTolerance = 0.01;
    std::unique_ptr<DcMotorEx> left = std::make_unique<DcMotorEx>("left",motorPowerTolerance);
    std::unique_ptr<DcMotorEx> right = std::make_unique<DcMotorEx>("right",motorPowerTolerance);
    std::unique_ptr<DcMotorEx> lift = std::make_unique<DcMotorEx>("lift",motorPowerTolerance);
    left->setDirection(&DcMotorEx::Direction::FORWARD);
    right->setDirection(&DcMotorEx::Direction::REVERSE);

    double ledColor = 0.280;
    float rainbowDirection = 1.0f;
    const double rainbowSpeed = 0.0000025;
    std::unique_ptr<Servo> led = std::make_unique<Servo>("led",0.001);

    waitForStart();

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        left->setPower(gamepad1->left_stick_y - gamepad1->left_stick_x);
        right->setPower(gamepad1->left_stick_y + gamepad1->left_stick_x);
        double liftDirection = (gamepad1->dpad_down) ? -1 : 1;
        lift->setPower((gamepad1->dpad_down || gamepad1->dpad_up) ? 0.5 * liftDirection : 0);


        if (ledColor > 0.720 || ledColor < 0.279)
            rainbowDirection = -rainbowDirection;
        ledColor += rainbowDirection * rainbowSpeed;
        led->setPosition(ledColor);
    }

    clearSDK(env);
}

TeleOp(Main, dummy);