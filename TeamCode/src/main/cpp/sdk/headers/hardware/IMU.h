#pragma once

#include "sdk/util/Util.h"
#include "sdk/headers/navigation/Orientation.h"



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
    jmethodID getRobotYawPitchRollAnglesID = nullptr;
    jmethodID resetYawID = nullptr;


public:

    inline static jclass imuClazz = nullptr;

    explicit IMU(const char* ImuName);

    ~IMU();

    bool initialize(Parameters::IMU::FacingDirection logoFacingDirection, Parameters::IMU::FacingDirection usbFacingDirection);

    void resetYaw();

    std::unique_ptr<YawPitchRollAngles> getRobotOrientation();
};


