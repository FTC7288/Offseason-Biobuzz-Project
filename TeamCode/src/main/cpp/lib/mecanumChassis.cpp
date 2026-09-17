#include "mecanumChassis.h"

MecanumChassis::MecanumChassis(std::unique_ptr<DcMotorEx> frontLeft,std::unique_ptr<DcMotorEx> frontRight,std::unique_ptr<DcMotorEx> backLeft,std::unique_ptr<DcMotorEx> backRight)
{
    frontLeft->setDirection(DcMotorEx::Direction::REVERSE);
    frontRight->setDirection(DcMotorEx::Direction::FORWARD);
    backLeft->setDirection(DcMotorEx::Direction::REVERSE);
    backRight->setDirection(DcMotorEx::Direction::FORWARD);
}

void MecanumChassis::driveFieldCentric(double stickY, double stickX, double stickRotation,double botHeading)
{
    double rotationX = stickX * cos(botHeading) - stickY * sin(botHeading);
    double rotationY = stickX * sin(botHeading) + stickY * cos(botHeading);

    double total = abs(rotationX + rotationY + stickRotation);
    double denominator = (total > 1) ? total : 1;

//    double frontLeftPower = (rotationY + rotationX + stickRotation) / denominator;
//    double frontRightPower = (rotationY - rotationX - stickRotation) / denominator;
//    double backLeftPower = (rotationY - rotationX + stickRotation) / denominator;
//    double backRightPower = (rotationY + rotationX - stickRotation) / denominator;

    frontLeft->setPower((rotationY + rotationX + stickRotation) / denominator);
    frontRight->setPower((rotationY - rotationX - stickRotation) / denominator);
    backLeft->setPower((rotationY - rotationX + stickRotation) / denominator);
    backRight->setPower((rotationY + rotationX - stickRotation) / denominator);
}
