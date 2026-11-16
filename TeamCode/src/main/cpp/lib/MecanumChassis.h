#pragma once

#include "sdk/Sdk.h"

struct Joystick {
public:
    double stickX;
    double stickY;
    double stickRotation;

    Joystick(double stickX, double stickY, double stickRotation);
};

class MecanumChassis {
private:
    DcMotorEx* frontLeft;
    DcMotorEx* frontRight;
    DcMotorEx* backLeft;
    DcMotorEx* backRight;



public:

    MecanumChassis(DcMotorEx* frontLeft,DcMotorEx* frontRight,DcMotorEx* backLeft,DcMotorEx* backRight);

    void toggleBrakeMode();
    void toggleFloatMode();

    void driveRobotCentric(double stickY, double stickX, double stickRotation);
    void driveFieldCentric(double stickY, double stickX, double stickRotation, double botHeading);

    Joystick straightLineFollower(const Pose2D &startPose, const Pose2D &endPose);
    Joystick curvedLineFollower(const Pose2D &startPose, const Pose2D &endPose);
};

