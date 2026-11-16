#include "sdk/headers/hardware/DcMotorEx.h"

DcMotorEx::DcMotorEx(const char *dcMotorName, double powerTolerance)
{
    JNIEnv* env = getEnv();
    this->dcMotorName = dcMotorName;
    jstring jdcMotorName = env->NewStringUTF(dcMotorName);
    dcMotorEx = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, dcMotorExClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setPowerID = env->GetMethodID(dcMotorExClazz, "setPower", "(D)V");
    setDirectionID = env->GetMethodID(dcMotorExClazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;)V");
    getVelocityID = env->GetMethodID(dcMotorExClazz, "getVelocity", "()D");
    setZeroPowerModeID = env->GetMethodID(dcMotorExClazz, "setZeroPowerBehavior", "(Lcom/qualcomm/robotcore/hardware/DcMotor$ZeroPowerBehavior;)V");
    //getCurrentPositionID = env->GetMethodID(dcMotorExClazz, "getCurrentPosition", "()D");

    motorPowerTolerance = powerTolerance;

    LOG_INFO("----- Creating DcMotorEx object '%s' -----", dcMotorName);
}

DcMotorEx::~DcMotorEx()
{
    JNIEnv* env = getEnv();

    if (dcMotorEx)
    {
        SAFE_DELETE_LOCAL(env, dcMotorEx);
        dcMotorEx = nullptr;
    }
}

void DcMotorEx::setPower(double desiredMotorPower)
{
    JNIEnv* env = getEnv();

    if (abs(currentMotorPower-desiredMotorPower) > motorPowerTolerance)
    {
        currentMotorPower = desiredMotorPower;
        env->CallVoidMethod(dcMotorEx, setPowerID, currentMotorPower);
    }
}

void DcMotorEx::setDirection(jobject* direction)
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(dcMotorEx, setDirectionID, *direction);

    const char* directionc_str = (*direction == Direction::FORWARD) ? "FORWARD" : "REVERSE";
    LOG_INFO("-------- Setting Motor Direction of '%s' to %s ---------", dcMotorName, directionc_str);
}

void DcMotorEx::setZeroPowerMode(jobject *zeroPowerMode)
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(dcMotorEx, setZeroPowerModeID, *zeroPowerMode);
    const char* behavior_str = (*zeroPowerMode == ZeroPowerMode::BRAKE) ? "BRAKE" : "FLOAT";
    LOG_INFO("-------- Setting Motor Zero Power Behavior of '%s' to %s ---------", dcMotorName, behavior_str);
}

double DcMotorEx::getVelocity()
{
    JNIEnv* env = getEnv();
    return env->CallDoubleMethod(dcMotorEx,getVelocityID);
}

double DcMotorEx::getCurrentPosition()
{
    JNIEnv* env = getEnv();
    return env->CallDoubleMethod(dcMotorEx,getCurrentPositionID);
}

