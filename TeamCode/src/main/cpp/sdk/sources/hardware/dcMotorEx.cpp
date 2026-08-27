#include "sdk/headers/hardware/dcMotorEx.h"

// TODO: ADD THE REST OF THE USED METHODS PLEASEEE!!
// TODO: ADD THE DIRECTION THING POR FLAVOR!!!!

DcMotorEx::DcMotorEx(const char *dcMotorName) {
    JNIEnv* env = getEnv();

    jclass hardwareMap = env->GetObjectClass(sdk::hardwareMap);
    jstring jdcMotorName = env->NewStringUTF(dcMotorName);
    dcMotorEx = env->CallObjectMethod(sdk::hardwareMap,env->GetMethodID(hardwareMap, "get", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Object;"), dcMotorExClazz, jdcMotorName);
    env->DeleteLocalRef(hardwareMap);
    env->DeleteLocalRef(jdcMotorName);

    setPowerID = env->GetMethodID(dcMotorExClazz, "setPower", "(D)V");
}

DcMotorEx::~DcMotorEx() {
    // TODO: clear global stuff
}

void DcMotorEx::setPower(double power) const {
    JNIEnv* env = getEnv();
    env->CallVoidMethod(dcMotorEx, setPowerID);
}
