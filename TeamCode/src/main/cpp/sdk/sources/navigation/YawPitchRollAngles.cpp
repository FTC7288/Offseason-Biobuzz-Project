#include "sdk/headers/navigation/YawPitchRollAngles.h"


YawPitchRollAngles::YawPitchRollAngles()
{
    JNIEnv *env = getEnv();

    getYawID = env->GetMethodID(yawPitchRollAnglesClazz, "getYaw", "(Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)D");
    getRollID = env->GetMethodID(yawPitchRollAnglesClazz, "getRoll", "(Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)D");
    getPitchID = env->GetMethodID(yawPitchRollAnglesClazz, "getPitch", "(Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)D");


}

YawPitchRollAngles::~YawPitchRollAngles()
{
//    JNIEnv* env = getEnv();
//
//    if (yawPitchRollAngles != nullptr)
//    {
//        SAFE_DELETE_LOCAL(env, yawPitchRollAngles);
//    }
}

double YawPitchRollAngles::getYaw(jobject angleUnit) const
{
    JNIEnv *env = getEnv();
    return env->CallDoubleMethod(yawPitchRollAngles, getYawID, angleUnit);
}

double YawPitchRollAngles::getRoll(jobject angleUnit) const
{
    JNIEnv *env = getEnv();
    return env->CallDoubleMethod(yawPitchRollAngles, getRollID, angleUnit);
}

double YawPitchRollAngles::getPitch(jobject angleUnit) const
{
    JNIEnv *env = getEnv();
    return env->CallDoubleMethod(yawPitchRollAngles, getPitchID, angleUnit);
}
