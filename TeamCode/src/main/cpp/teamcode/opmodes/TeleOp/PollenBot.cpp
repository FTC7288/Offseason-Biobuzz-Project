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

    double desiredVelocity = 1180;
    double shooterVelocity = 0;
    double shooterPower = 0;
    bool atSpeed = false;
    DcMotorEx shooter {"shooter", 0};
    shooter.setDirection(&DcMotorEx::Direction::REVERSE);

    double intakePower = 0;
    DcMotorEx intake {"intake", 0};
    shooter.setDirection(&DcMotorEx::Direction::REVERSE);

    const double downPos = 0.4;
    const double upPos = 0.75;
    Servo stop {"stop", 0};


    std::unique_ptr<IMU> imu = std::make_unique<IMU>("imu");

    LOG_INFO("---------- initialized IMU -------");
    imu->initialize(Parameters::IMU::FacingDirection::RIGHT, Parameters::IMU::FacingDirection::UP);

    SparkFunOTOS otos {"otos"};
    otos.setAngularUnit(&AngleUnit::DEGREES);
    otos.setAngularScalar(1.0034);
    otos.setLinearUnit(&DistanceUnit::CM);
    otos.setLinearScalar(1);
    otos.setPosition(new Pose2D(-9.651,0,180));

    waitForStart();

    otos.begin();

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        if (gamepad1->start)
        {
            imu->resetYaw();
        }

        telemetry::addData("Pose X", std::to_string(otos.getPosition()->x).c_str());
        telemetry::addData("Pose Y", std::to_string(otos.getPosition()->y).c_str());
        telemetry::addData("Heading", std::to_string(otos.getPosition()->h).c_str());



        double imuAngle = imu->getYawPitchRollAngles()->getYaw(AngleUnit::RADIANS);
        robotChassis.driveFieldCentric(gamepad1->left_stick_y, -gamepad1->left_stick_x, -gamepad1->right_stick_x,imuAngle);



        if (gamepad1->dpad_up)
        {
            desiredVelocity += 5;
        }
        else if (gamepad1->dpad_down)
        {
            desiredVelocity -= 5;
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
        } else
        {
            atSpeed = true;
            shooterPower = 0;
        }

        if (gamepad1->b)
        {
            shooter.setPower(shooterPower);
        }
        else
        {
            atSpeed = false;
            shooter.setPower(0);
        }

        telemetry::addData("Shooter Power", std::to_string(shooterPower).c_str());


        if (gamepad1->rightTriggerDown() || atSpeed)
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

        if (atSpeed)
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