#pragma once

#include "sdk/util/Util.h"
#include "sdk/headers/navigation/Orientation.h"
#include "sdk/headers/navigation/YawPitchRollAngles.h"
#include "sdk/headers/navigation/AngleUnit.h"



namespace Parameters::IMU
{
    inline jclass parametersClazz = nullptr;
    inline jclass revHubOrientationOnRobotClazz = nullptr;
    inline jclass logoFacingDirectionClazz = nullptr;
    inline jclass usbFacingDirectionClazz = nullptr;

    enum FacingDirection
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD
    };

    static const char* toString[] = {"UP","DOWN","LEFT","RIGHT","FORWARD","BACKWARD"};
};



class IMU
{
private:
    jobject imu = nullptr;

    jmethodID initializeID = nullptr;
    jmethodID getRobotOrientationID = nullptr;
    jmethodID getRobotYawPitchRollAnglesID = nullptr;
    jmethodID resetYawID = nullptr;

    Orientation orientation;

    YawPitchRollAngles yawPitchRollAngles;
    jobject globalYawPitchRollAngles = nullptr;

    void updateOrientation();

public:


    inline static jclass imuClazz = nullptr;

    explicit IMU(const char* ImuName);

    ~IMU();

    bool initialize(Parameters::IMU::FacingDirection logoFacingDirection, Parameters::IMU::FacingDirection usbFacingDirection);

    void resetYaw();

    const Orientation* getRobotOrientation();
    const YawPitchRollAngles* getYawPitchRollAngles();
};


