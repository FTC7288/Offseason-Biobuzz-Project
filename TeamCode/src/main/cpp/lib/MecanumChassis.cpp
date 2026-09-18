#include "MecanumChassis.h"

#include <utility>

MecanumChassis::MecanumChassis(std::shared_ptr<DcMotorEx> frontLeft,std::shared_ptr<DcMotorEx> frontRight,std::shared_ptr<DcMotorEx> backLeft,std::shared_ptr<DcMotorEx> backRight)
{
    this->frontLeft = std::move(frontLeft);
    this->frontRight = std::move(frontRight);
    this->backLeft = std::move(backLeft);
    this->backRight = std::move(backRight);

    this->frontLeft->setDirection(DcMotorEx::Direction::REVERSE);
    this->frontRight->setDirection(DcMotorEx::Direction::FORWARD);
    this->backLeft->setDirection(DcMotorEx::Direction::REVERSE);
    this->backRight->setDirection(DcMotorEx::Direction::FORWARD);
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

void MecanumChassis::driveRobotCentric(double stickY, double stickX, double stickRotation)
{
    frontLeft->setPower(stickY + stickX + stickRotation);
    frontRight->setPower(stickY - stickX - stickRotation);
    backLeft->setPower(stickY + stickX - stickRotation);
    backRight->setPower(stickY - stickX + stickRotation);
}
