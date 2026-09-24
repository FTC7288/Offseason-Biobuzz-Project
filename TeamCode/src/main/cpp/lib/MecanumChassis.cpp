#include "MecanumChassis.h"

#include <utility>

MecanumChassis::MecanumChassis(DcMotorEx* frontLeft, DcMotorEx* frontRight, DcMotorEx* backLeft, DcMotorEx* backRight)
: frontLeft(frontLeft), frontRight(frontRight), backLeft(backLeft), backRight(backRight)
{}

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

void MecanumChassis::driveFieldCentric(double stickY, double stickX, double stickRotation,double botHeading)
{
    double theta = std::atan2(stickY,stickX);
    double r = std::hypot(stickX,stickY);

    theta = std::remainder(theta - botHeading,2.0 * M_PI);

    stickY = r * std::sin(theta);
    stickX = r * std::cos(theta);

    driveRobotCentric(stickY, stickX, stickRotation);
}


