#include "sdk/headers/hardware/dcMotorEx.h"

// TODO: ADD THE REST OF THE USED METHODS PLEASEEE!!
// TODO: ADD THE DIRECTION THING POR FLAVOR!!!!

DcMotorEx::DcMotorEx(const char *dcMotorName)
{
    JNIEnv* env = getEnv();

    jstring jdcMotorName = env->NewStringUTF(dcMotorName);
    dcMotorEx = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, dcMotorExClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setPowerID = env->GetMethodID(dcMotorExClazz, "setPower", "(D)V");
}

DcMotorEx::~DcMotorEx()
{
    // TODO: clear global stuff
}

void DcMotorEx::setPower(double power) const
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(dcMotorEx, setPowerID);
}

void DcMotorEx::setDirection(const DcMotorEx::Direction &direction) const
{
    JNIEnv* env = getEnv();
    jobject jdirection = env->GetStaticObjectField(directionClazz, env->GetStaticFieldID(directionClazz,(direction == Direction::FORWARD) ? "FORWARD" : "REVERSE" ,"Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;"));
    env->CallVoidMethod(dcMotorEx, env->GetMethodID(dcMotorExClazz, "setDirection", "(Lcom/qualcomm/robotcore/hardware/DcMotorSimple$Direction;)V"), jdirection);
    env->DeleteLocalRef(jdirection);
}
