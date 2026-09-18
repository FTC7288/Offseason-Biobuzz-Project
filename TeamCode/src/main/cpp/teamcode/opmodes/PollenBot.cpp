#include "sdk/Sdk.h"
#include "lib/CustomLib.hpp"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void PollenBot(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);

    const double driveMotorPowerTolerance = 0.05;

    std::shared_ptr<DcMotorEx> frontLeft = std::make_shared<DcMotorEx>("fl", driveMotorPowerTolerance);
    std::shared_ptr<DcMotorEx> frontRight = std::make_shared<DcMotorEx>("fr", driveMotorPowerTolerance);
    std::shared_ptr<DcMotorEx> backLeft = std::make_shared<DcMotorEx>("bl",driveMotorPowerTolerance);
    std::shared_ptr<DcMotorEx> backRight = std::make_shared<DcMotorEx>("br", driveMotorPowerTolerance);

    MecanumChassis robotChassis = MecanumChassis(
            frontLeft,
            frontRight,
            backLeft,
            backRight
            );


    waitForStart();

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        robotChassis.driveRobotCentric((double)gamepad1->left_stick_y, (double)gamepad1->left_stick_x, (double)gamepad1->right_stick_x);
    }

    deleteSDK(env);
}

TeleOp(PollenBot, dummy)