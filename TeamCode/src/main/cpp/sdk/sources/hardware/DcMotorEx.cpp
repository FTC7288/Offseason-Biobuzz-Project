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
    //getVelocityID = env->GetMethodID(dcMotorExClazz, "getVelocity", "()D");
    //getCurrentPositionID = env->GetMethodID(dcMotorExClazz, "getCurrentPosition", "()D");

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
    const char* directionc_str = (direction == Direction::FORWARD) ? "FORWARD" : "REVERSE";
    jobject jdirection = env->GetStaticObjectField(directionClazz, env->GetStaticFieldID(directionClazz,directionc_str ,"Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;"));

    env->CallVoidMethod(dcMotorEx, setDirectionID, jdirection);
    SAFE_DELETE_LOCAL(env, jdirection);
    LOG_INFO("-------- Setting Motor Direction of '%s' to %s ---------", dcMotorName, directionc_str);
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
