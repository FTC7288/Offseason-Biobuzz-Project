#include "sdk/Sdk.h"
#include "lib/CustomLib.h"

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

    frontLeft->setDirection(&DcMotorEx::Direction::FORWARD);
    frontRight->setDirection(&DcMotorEx::Direction::FORWARD);
    backLeft->setDirection(&DcMotorEx::Direction::FORWARD);
    backRight->setDirection(&DcMotorEx::Direction::FORWARD);

    MecanumChassis robotChassis = MecanumChassis(
            frontLeft,
            frontRight,
            backLeft,
            backRight
            );

    double shooterPower = 0;
    std::unique_ptr<DcMotorEx> shooter = std::make_unique<DcMotorEx>("gun",0);
    shooter->setDirection(&DcMotorEx::Direction::FORWARD);


    std::unique_ptr<IMU> imu = std::make_unique<IMU>("imu");

    LOG_INFO("---------- initialized IMU -------");
    imu->initialize(Parameters::IMU::FacingDirection::UP, Parameters::IMU::FacingDirection::BACKWARD);


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
            shooterPower += 0.01;
        } else if (gamepad1->dpad_down)
        {
            shooterPower -= 0.01;
        }
        shooter->setPower(shooterPower);
        telemetry::addData("Shooter Power", std::to_string(shooterPower).c_str());
    }

    deleteSDK(env);
}

TeleOp(PollenBot, dummy)