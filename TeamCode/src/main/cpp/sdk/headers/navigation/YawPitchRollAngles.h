#pragma once

#include "sdk/util/Util.h"
#include "sdk/headers/navigation/AngleUnit.h"

struct YawPitchRollAngles
{
private:
    inline static jmethodID getYawID = nullptr;
    inline static jmethodID getRollID = nullptr;
    inline static jmethodID getPitchID = nullptr;

public:
    jobject yawPitchRollAngles = nullptr;

    inline static jclass yawPitchRollAnglesClazz = nullptr;

    YawPitchRollAngles();
    ~YawPitchRollAngles();

    double getYaw(jobject angleUnit) const;
    double getRoll(jobject angleUnit) const;
    double getPitch(jobject angleUnit) const;

};

