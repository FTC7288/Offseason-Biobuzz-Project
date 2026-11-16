#include "MecanumChassis.h"

#include <utility>

Joystick::Joystick(double stickX, double stickY, double stickRotation)
{
    this->stickX = stickX;
    this->stickY = stickY;
    this->stickRotation = stickRotation;
}

MecanumChassis::MecanumChassis(DcMotorEx* frontLeft, DcMotorEx* frontRight, DcMotorEx* backLeft, DcMotorEx* backRight)
: frontLeft(frontLeft), frontRight(frontRight), backLeft(backLeft), backRight(backRight)
{}

void MecanumChassis::toggleBrakeMode()
{
    frontLeft->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::BRAKE);
    frontRight->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::BRAKE);
    backLeft->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::BRAKE);
    backRight->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::BRAKE);
}

void MecanumChassis::toggleFloatMode()
{
    frontLeft->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::FLOAT);
    frontRight->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::FLOAT);
    backLeft->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::FLOAT);
    backRight->setZeroPowerMode(&DcMotorEx::ZeroPowerMode::FLOAT);
}

void MecanumChassis::driveRobotCentric(double stickY, double stickX, double stickRotation)
{
    double frontLeftPower = stickY + stickX + stickRotation;
    double frontRightPower = stickY - stickX - stickRotation;
    double backLeftPower = stickY - stickX + stickRotation;
    double backRightPower = stickY + stickX - stickRotation;

    double maxPower = std::max({std::abs(frontLeftPower), std::abs(frontRightPower), std::abs(backLeftPower), std::abs(backRightPower)});

    if (maxPower > 1)
    {
        frontLeftPower /= maxPower;
        frontRightPower /= maxPower;
        backLeftPower /= maxPower;
        backRightPower /= maxPower;
    }
    frontLeft->setPower(frontLeftPower);
    frontRight->setPower(frontRightPower);
    backLeft->setPower(backLeftPower);
    backRight->setPower(backRightPower);
}

void MecanumChassis::driveFieldCentric(double stickY, double stickX, double stickRotation, double botHeading)
{
    double theta = std::atan2(stickY,stickX);
    double r = std::hypot(stickX,stickY);

    theta = std::remainder(theta - botHeading,2.0 * M_PI);

    stickY = r * std::sin(theta);
    stickX = r * std::cos(theta);

    driveRobotCentric(stickY, stickX, stickRotation);
}

Joystick MecanumChassis::straightLineFollower(const Pose2D &startPose, const Pose2D &endPose)
{
    double theta = std::atan2(endPose.y - startPose.y, endPose.x - startPose.x);
    double xOut = std::cos(theta);
    double yOut = std::sin(theta);

    return {-xOut,-yOut,0};
}

// TODO: Implement curved line follower
Joystick MecanumChassis::curvedLineFollower(const Pose2D &startPose, const Pose2D &endPose)
{

    return {0,0,0};
}





