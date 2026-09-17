#include "sdk/headers/hardware/IMU.h"


IMU::IMU(const char *ImuName)
{
    JNIEnv* env = getEnv();

    jstring jImuName = env->NewStringUTF(ImuName);
    imu = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, imuClazz, jImuName);
    env->DeleteLocalRef(jImuName);

    initializeID = env->GetMethodID(imuClazz, "initialize", "(Lcom/qualcomm/robotcore/hardware/IMU$Parameters;)Z");
    resetYawID = env->GetMethodID(imuClazz, "resetYaw", "()V");
    getRobotYawPitchRollAnglesID = env->GetMethodID(imuClazz, "getRobotOrientation", "()Lorg/firstinspires/ftc/robotcore/external/navigation/Orientation;");

}

IMU::~IMU() {
    JNIEnv *env = getEnv();

    if (imuClazz) {
        env->DeleteGlobalRef(imuClazz);
        imuClazz = nullptr;
    }
    if (Parameters::IMU::revHubOrientationOnRobotClazz) {
        env->DeleteGlobalRef(Parameters::IMU::revHubOrientationOnRobotClazz);
        Parameters::IMU::revHubOrientationOnRobotClazz = nullptr;
    }
    if (Parameters::IMU::parametersClazz) {
        env->DeleteGlobalRef(Parameters::IMU::parametersClazz);
        Parameters::IMU::parametersClazz = nullptr;
    }
    if (Parameters::IMU::logoFacingDirectionClazz) {
        env->DeleteGlobalRef(Parameters::IMU::logoFacingDirectionClazz);
        Parameters::IMU::logoFacingDirectionClazz = nullptr;
    }
    if (Parameters::IMU::usbFacingDirectionClazz)
    {
        env->DeleteGlobalRef(Parameters::IMU::usbFacingDirectionClazz);
        Parameters::IMU::usbFacingDirectionClazz = nullptr;
    }
    if (imu)
    {
        env->DeleteLocalRef(imu);
        imu = nullptr;
    }
}

bool IMU::initialize(const Parameters::IMU::FacingDirection logoFacingDirection, const Parameters::IMU::FacingDirection usbFacingDirection)
{
    JNIEnv* env = getEnv();

    jmethodID jCtorParameters = env->GetMethodID(
            Parameters::IMU::parametersClazz,
            "<init>",
            "(Lcom/qualcomm/robotcore/hardware/ImuOrientationOnRobot;)V"
    );
    jmethodID jCtorRevHubOrientationOnRobot = env->GetMethodID(
            Parameters::IMU::revHubOrientationOnRobotClazz,
            "<init>",
            "(Lcom/qualcomm/hardware/rev/RevHubOrientationOnRobot$LogoFacingDirection;Lcom/qualcomm/hardware/rev/RevHubOrientationOnRobot$UsbFacingDirection;)V"
            );
    jfieldID jfieldLogoFacingDirection = env->GetStaticFieldID(
            Parameters::IMU::logoFacingDirectionClazz,
            Parameters::IMU::toString[logoFacingDirection],
            "Lcom/qualcomm/hardware/rev/RevHubOrientationOnRobot$LogoFacingDirection;"
            );
    jfieldID jfieldUsbFacingDirection = env->GetStaticFieldID(
            Parameters::IMU::usbFacingDirectionClazz,
            Parameters::IMU::toString[usbFacingDirection],
            "Lcom/qualcomm/hardware/rev/RevHubOrientationOnRobot$UsbFacingDirection;"
            );

    jobject jLogoFacingDirection = env->GetStaticObjectField(
            Parameters::IMU::logoFacingDirectionClazz, jfieldLogoFacingDirection
    );
    jobject jUsbFacingDirection = env->GetStaticObjectField(
            Parameters::IMU::usbFacingDirectionClazz, jfieldUsbFacingDirection
    );

    jobject revHubOrientationOnRobot = env->NewObject(Parameters::IMU::revHubOrientationOnRobotClazz, jCtorRevHubOrientationOnRobot, jLogoFacingDirection, jUsbFacingDirection);
    jobject parameters = env->NewObject(Parameters::IMU::parametersClazz,jCtorParameters,revHubOrientationOnRobot);

    return env->CallBooleanMethod(imu, initializeID, parameters);
    env->DeleteLocalRef(revHubOrientationOnRobot);
    env->DeleteLocalRef(parameters);
    env->DeleteLocalRef(jLogoFacingDirection);
    env->DeleteLocalRef(jUsbFacingDirection);

}

void IMU::resetYaw()
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(imu,resetYawID);
}

std::unique_ptr<Orientation> IMU::getRobotOrientation()
{
    return {}; // TODO: FINISH MEEEEEEEEE
}



