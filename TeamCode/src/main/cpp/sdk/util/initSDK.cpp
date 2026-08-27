#include "initSDK.h"


void initSDK(JNIEnv* env)
{
    if (sdk::opmode == nullptr)
    {
        LOG_ERROR("__________________________ COULD NOT FIND sdk::opmode _______________________________");
        return;
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


    jobject localHardwareMap = env->GetObjectField(*sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "hardwareMap", "Lcom/qualcomm/robotcore/hardware/HardwareMap;"));
    sdk::hardwareMap = env->NewGlobalRef(localHardwareMap);
    env->DeleteLocalRef(localHardwareMap);


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


}