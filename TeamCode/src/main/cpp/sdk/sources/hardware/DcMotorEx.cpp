#include "sdk/headers/hardware/DcMotorEx.h"

// TODO: Add getPosition() and getVelocity()

DcMotorEx::DcMotorEx(const char *dcMotorName, double powerTolerance)
{
    JNIEnv* env = getEnv();

    jstring jdcMotorName = env->NewStringUTF(dcMotorName);
    dcMotorEx = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, dcMotorExClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setPowerID = env->GetMethodID(dcMotorExClazz, "setPower", "(D)V");
    setDirectionID = env->GetMethodID(dcMotorExClazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;)V");
    motorPowerTolerance = powerTolerance;
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

void DcMotorEx::setDirection(const DcMotorEx::Direction &direction) const
{
    JNIEnv* env = getEnv();
    jobject jdirection = env->GetStaticObjectField(directionClazz, env->GetStaticFieldID(directionClazz,(direction == Direction::FORWARD) ? "FORWARD" : "REVERSE" ,"Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;"));
    env->CallVoidMethod(dcMotorEx, setDirectionID, jdirection);
    SAFE_DELETE_LOCAL(env, jdirection);
}
