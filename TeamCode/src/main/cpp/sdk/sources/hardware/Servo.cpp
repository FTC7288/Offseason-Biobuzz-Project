#include "sdk/headers/hardware/Servo.h"


Servo::Servo(const char *servoName, double positionTolerance) {
    JNIEnv* env = getEnv();

    jstring jdcMotorName = env->NewStringUTF(servoName);
    servo = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, servoClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setPositionID = env->GetMethodID(servoClazz, "setPosition", "(D)V");
    servoPositionTolerance = positionTolerance;
}

Servo::~Servo() {
    JNIEnv* env = getEnv();

    if (servo)
    {
        SAFE_DELETE_LOCAL(env,servo);
    }
}

void Servo::setPosition(double desiredPosition) {
    JNIEnv* env = getEnv();

    if (abs(currentServoPosition-desiredPosition) > servoPositionTolerance)
    {
        currentServoPosition = desiredPosition;
        env->CallVoidMethod(servo, setPositionID, currentServoPosition);
    }
}
