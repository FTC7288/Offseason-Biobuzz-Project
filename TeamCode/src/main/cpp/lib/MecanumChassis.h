#pragma once

#include "sdk/Sdk.h"

class MecanumChassis {
private:
    DcMotorEx* frontLeft;
    DcMotorEx* frontRight;
    DcMotorEx* backLeft;
    DcMotorEx* backRight;



public:

    MecanumChassis(DcMotorEx* frontLeft,DcMotorEx* frontRight,DcMotorEx* backLeft,DcMotorEx* backRight);

    void driveRobotCentric(double stickY, double stickX, double stickRotation);
    void driveFieldCentric(double stickY, double stickX, double stickRotation, double botHeading);

};

