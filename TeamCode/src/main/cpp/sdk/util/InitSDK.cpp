#include "InitSDK.h"


void initSDK(JNIEnv* env, jobject* thiz)
{
    if (thiz == nullptr)
    {
        LOG_ERROR("__________________________ COULD NOT FIND sdk::opmode _______________________________");
        return;
    }
    else
    {
        sdk::opmode = thiz;
    }

    jclass localClazz = env->GetObjectClass(*sdk::opmode);
    linearOpMode::linearOpModeClazz = reinterpret_cast<jclass>(env->NewGlobalRef(localClazz));
    env->DeleteLocalRef(localClazz);

    linearOpMode::cachedMethodIDs::idleID = env->GetMethodID(linearOpMode::linearOpModeClazz, "idle", "()V");
    linearOpMode::cachedMethodIDs::terminateOpModeNowID = env->GetMethodID(linearOpMode::linearOpModeClazz, "terminateOpModeNow", "()V");
    linearOpMode::cachedMethodIDs::waitForStartID = env->GetMethodID(linearOpMode::linearOpModeClazz, "waitForStart", "()V");
    linearOpMode::cachedMethodIDs::opModeInInitID = env->GetMethodID(linearOpMode::linearOpModeClazz, "opModeInInit", "()Z");
    linearOpMode::cachedMethodIDs::isStopRequestedID = env->GetMethodID(linearOpMode::linearOpModeClazz, "isStopRequested", "()Z");
    linearOpMode::cachedMethodIDs::opModeIsActiveID = env->GetMethodID(linearOpMode::linearOpModeClazz, "opModeIsActive", "()Z");


    jobject localHardwareMapObject = env->GetObjectField(*sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "hardwareMap", "Lcom/qualcomm/robotcore/hardware/HardwareMap;"));
    sdk::hardwareMap = env->NewGlobalRef(localHardwareMapObject);
    jclass localhardwareMapClass = env->GetObjectClass(sdk::hardwareMap);
    sdk::getID = env->GetMethodID(localhardwareMapClass, "get", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Object;");
    env->DeleteLocalRef(localHardwareMapObject);
    env->DeleteLocalRef(localhardwareMapClass);


    telemetry::telemetryClazz = findAndCreateGlobalRef(env, "org/firstinspires/ftc/robotcore/external/Telemetry");
    jobject localTelemetryObject = env->GetObjectField(*sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "telemetry", "Lorg/firstinspires/ftc/robotcore/external/Telemetry;"));
    telemetry::telemetry = env->NewGlobalRef(localTelemetryObject);
    env->DeleteLocalRef(localTelemetryObject);

    telemetry::cachedMethodIDs::updateID = env->GetMethodID(telemetry::telemetryClazz, "update", "()Z");
    telemetry::cachedMethodIDs::addDataID = env->GetMethodID(telemetry::telemetryClazz, "addData", "(Ljava/lang/String;Ljava/lang/Object;)Lorg/firstinspires/ftc/robotcore/external/Telemetry$Item;");;
    telemetry::cachedMethodIDs::addLineID = env->GetMethodID(telemetry::telemetryClazz, "addLine", "(Ljava/lang/String;)Lorg/firstinspires/ftc/robotcore/external/Telemetry$Line;");;


    Gamepad::gamepadClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/Gamepad");
    jobject localGamepad1 = env->GetObjectField(*sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "gamepad1", "Lcom/qualcomm/robotcore/hardware/Gamepad;"));
    gamepads::gamepad1 = std::make_unique<Gamepad>(env->NewGlobalRef(localGamepad1));
    env->DeleteLocalRef(localGamepad1);

    jobject localGamepad2 = env->GetObjectField(*sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "gamepad1", "Lcom/qualcomm/robotcore/hardware/Gamepad;"));
    gamepads::gamepad2 = std::make_unique<Gamepad>(env->NewGlobalRef(localGamepad2));
    env->DeleteLocalRef(localGamepad2);


    DcMotorEx::dcMotorExClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/DcMotorEx");
    DcMotorEx::directionClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/DcMotorSimple$Direction");
    Servo::servoClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/Servo");
    LynxModule::lynxModuleClazz = findAndCreateGlobalRef(env, "com/qualcomm/hardware/lynx/LynxModule");
    LynxModule::bulkCachingModeClazz = findAndCreateGlobalRef(env, "com/qualcomm/hardware/lynx/LynxModule$BulkCachingMode");
    IMU::imuClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/IMU");
    Parameters::IMU::parametersClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/IMU$Parameters");
    Parameters::IMU::revHubOrientationOnRobotClazz = findAndCreateGlobalRef(env, "com/qualcomm/hardware/rev/RevHubOrientationOnRobot");
    Parameters::IMU::logoFacingDirectionClazz = findAndCreateGlobalRef(env, "com/qualcomm/hardware/rev/RevHubOrientationOnRobot$LogoFacingDirection");
    Parameters::IMU::usbFacingDirectionClazz = findAndCreateGlobalRef(env, "com/qualcomm/hardware/rev/RevHubOrientationOnRobot$UsbFacingDirection");


}