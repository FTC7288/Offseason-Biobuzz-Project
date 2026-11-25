#include "sdk/Sdk.h"
#include "lib/CustomLib.h"
#include "teamcode/global/Robot.hpp"

using namespace linearOpMode;
using namespace gamepads;
using namespace Robot;


extern "C" void DriveAround(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);
    Robot::init();
    double desiredVelocity = 1180;
    double shooterVelocity = 0;
    double shooterPower = 0;

    waitForStart();

    otos->begin();
    stop->setPosition(Robot::Constants::STOP_UP_POS);

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        if (gamepad1->start)
        {
            imu->resetYaw();
        }
        double imuAngle = imu->getYawPitchRollAngles()->getYaw(AngleUnit::RADIANS);
        robotChassis->driveFieldCentric(gamepad1->left_stick_y, -gamepad1->left_stick_x, -gamepad1->right_stick_x,imuAngle);


        if (gamepad1->dpad_up)
        {
            desiredVelocity += 5;
        }
        else if (gamepad1->dpad_down)
        {
            desiredVelocity -= 5;
        }
        shooterVelocity = shooter->getVelocity();
        telemetry::addData("Shooter Velocity", std::to_string(shooterVelocity).c_str());
        telemetry::addData("Desired Velocity", std::to_string(desiredVelocity).c_str());
        if (shooterVelocity < desiredVelocity - 10)
        {
            shooterPower = 1;
        } else if (shooterVelocity > desiredVelocity + 10)
        {
            shooterPower = 0;
        } else
        {
            shooterPower = 0;
        }
        shooter->setPower(shooterPower);
        telemetry::addData("Shooter Power", std::to_string(shooterPower).c_str());


        if (gamepad1->rightTriggerDown())
        {
            intake->setPower(Robot::Constants::INTAKE_POWER);
        }
        else if (gamepad1->leftTriggerDown())
        {
            intake->setPower(Robot::Constants::OUTTAKE_POWER);
        }
        else
        {
            intake->setPower(Robot::Constants::INTAKE_OFF_POWER);
        }
    }

    clearSDK(env);
}

TeleOp(DriveAround, dummy)