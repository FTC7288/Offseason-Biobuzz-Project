#pragma once

#include "sdk/Sdk.h"

class MecanumChassis {
private:
    std::unique_ptr<DcMotorEx> frontLeft = nullptr;
    std::unique_ptr<DcMotorEx> frontRight = nullptr;
    std::unique_ptr<DcMotorEx> backLeft = nullptr;
    std::unique_ptr<DcMotorEx> backRight = nullptr;



public:

    MecanumChassis(std::unique_ptr<DcMotorEx> frontLeft,std::unique_ptr<DcMotorEx> frontRight,std::unique_ptr<DcMotorEx> backLeft,std::unique_ptr<DcMotorEx> backRight);

    void driveFieldCentric(double stickY, double stickX, double stickRotation, double botHeading);



};

