#include "sdk/Sdk.h"
#include "lib/CustomLib.h"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void PollenBot(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);

    const double driveMotorPowerTolerance = 0.05;

    DcMotorEx frontLeft {"fl" , driveMotorPowerTolerance};
    DcMotorEx frontRight {"fr" , driveMotorPowerTolerance};
    DcMotorEx backLeft {"bl" , driveMotorPowerTolerance};
    DcMotorEx backRight {"br" , driveMotorPowerTolerance};

    frontLeft.setDirection(&DcMotorEx::Direction::FORWARD);
    frontRight.setDirection(&DcMotorEx::Direction::REVERSE);
    backLeft.setDirection(&DcMotorEx::Direction::FORWARD);
    backRight.setDirection(&DcMotorEx::Direction::REVERSE);

    MecanumChassis robotChassis = MecanumChassis(
            &frontLeft,
            &frontRight,
            &backLeft,
            &backRight
            );

    double desiredVelocity = 0;
    double shooterVelocity = 0;
    double shooterPower = 0;
    DcMotorEx shooter {"shooter", 0};
    shooter.setDirection(&DcMotorEx::Direction::REVERSE);

    double intakePower = 0;
    DcMotorEx intake {"intake", 0};
    shooter.setDirection(&DcMotorEx::Direction::REVERSE);

    const double downPos = 0.35;
    const double upPos = 0.8;
    Servo stop {"stop", 0};


    std::unique_ptr<IMU> imu = std::make_unique<IMU>("imu");

    LOG_INFO("---------- initialized IMU -------");
    imu->initialize(Parameters::IMU::FacingDirection::RIGHT, Parameters::IMU::FacingDirection::UP);


    waitForStart();

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        if (gamepad1->start)
        {
            imu->resetYaw();
        }

        double imuAngle = imu->getYawPitchRollAngles()->getYaw(AngleUnit::RADIANS);
        robotChassis.driveFieldCentric(gamepad1->left_stick_y, -gamepad1->left_stick_x, -gamepad1->right_stick_x,imuAngle);
        telemetry::addData("IMU ANGLE", std::to_string(imuAngle).c_str());


        if (gamepad1->dpad_up)
        {
            desiredVelocity += 10;
        }
        else if (gamepad1->dpad_down)
        {
            desiredVelocity -= 10;
        }

        shooterVelocity = shooter.getVelocity();
        telemetry::addData("Shooter Velocity", std::to_string(shooterVelocity).c_str());
        telemetry::addData("Desired Velocity", std::to_string(desiredVelocity).c_str());

        if (shooterVelocity < desiredVelocity - 10)
        {
            shooterPower = 1;
        } else if (shooterVelocity > desiredVelocity + 10)
        {
            shooterPower = 0;
        }


        if (gamepad1->b)
        {
            shooter.setPower(shooterPower);
        }
        else
        {
            shooter.setPower(0);
        }

        telemetry::addData("Shooter Power", std::to_string(shooterPower).c_str());


        if (gamepad1->rightTriggerDown())
        {
            intakePower = -1;
        }
        else if (gamepad1->leftTriggerDown())
        {
            intakePower = 1;
        }
        else
        {
            intakePower = 0;
        }
        intake.setPower(intakePower);

        if (gamepad1->left_bumper)
        {
            stop.setPosition(downPos);
        }
        else
        {
            stop.setPosition(upPos);
        }
    }

    clearSDK(env);
}

TeleOp(PollenBot, dummy)