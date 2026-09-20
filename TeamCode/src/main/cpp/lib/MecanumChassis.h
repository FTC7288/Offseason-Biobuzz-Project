#pragma once

#include "sdk/Sdk.h"

class MecanumChassis {
private:
    std::shared_ptr<DcMotorEx> frontLeft = nullptr;
    std::shared_ptr<DcMotorEx> frontRight = nullptr;
    std::shared_ptr<DcMotorEx> backLeft = nullptr;
    std::shared_ptr<DcMotorEx> backRight = nullptr;



public:

    MecanumChassis(std::shared_ptr<DcMotorEx> frontLeft,std::shared_ptr<DcMotorEx> frontRight,std::shared_ptr<DcMotorEx> backLeft,std::shared_ptr <DcMotorEx> backRight);

    void driveRobotCentric(double stickY, double stickX, double stickRotation);
    void driveFieldCentric(double stickY, double stickX, double stickRotation, double botHeading);

};

