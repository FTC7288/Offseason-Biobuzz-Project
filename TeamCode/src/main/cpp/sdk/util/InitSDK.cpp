#include "InitSDK.h"


void initSDK(JNIEnv* env, jobject thiz)
{
    if (thiz == nullptr)
    {
        LOG_ERROR("__________________________ COULD NOT FIND sdk::opmode _______________________________");
        return;
    }

    if (sdk::opmode != nullptr)
    {
        env->DeleteGlobalRef(sdk::opmode);
    }
    sdk::opmode = env->NewGlobalRef(thiz);

    jclass localClazz = env->GetObjectClass(sdk::opmode);
    linearOpMode::linearOpModeClazz = reinterpret_cast<jclass>(env->NewGlobalRef(localClazz));
    SAFE_DELETE_LOCAL(env, localClazz);

    linearOpMode::cachedMethodIDs::idleID = env->GetMethodID(linearOpMode::linearOpModeClazz, "idle", "()V");
    linearOpMode::cachedMethodIDs::terminateOpModeNowID = env->GetMethodID(linearOpMode::linearOpModeClazz, "terminateOpModeNow", "()V");
    linearOpMode::cachedMethodIDs::waitForStartID = env->GetMethodID(linearOpMode::linearOpModeClazz, "waitForStart", "()V");
    linearOpMode::cachedMethodIDs::opModeInInitID = env->GetMethodID(linearOpMode::linearOpModeClazz, "opModeInInit", "()Z");
    linearOpMode::cachedMethodIDs::isStopRequestedID = env->GetMethodID(linearOpMode::linearOpModeClazz, "isStopRequested", "()Z");
    linearOpMode::cachedMethodIDs::opModeIsActiveID = env->GetMethodID(linearOpMode::linearOpModeClazz, "opModeIsActive", "()Z");


    jobject localHardwareMapObject = env->GetObjectField(sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "hardwareMap", "Lcom/qualcomm/robotcore/hardware/HardwareMap;"));
    sdk::hardwareMap = env->NewGlobalRef(localHardwareMapObject);
    jclass localhardwareMapClass = env->GetObjectClass(sdk::hardwareMap);
    sdk::getID = env->GetMethodID(localhardwareMapClass, "get", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Object;");
    SAFE_DELETE_LOCAL(env, localHardwareMapObject);
    SAFE_DELETE_LOCAL(env, localhardwareMapClass);


    telemetry::telemetryClazz = findAndCreateGlobalRef(env, "org/firstinspires/ftc/robotcore/external/Telemetry");
    jobject localTelemetryObject = env->GetObjectField(sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "telemetry", "Lorg/firstinspires/ftc/robotcore/external/Telemetry;"));
    telemetry::telemetry = env->NewGlobalRef(localTelemetryObject);
    SAFE_DELETE_LOCAL(env, localTelemetryObject);

    telemetry::cachedMethodIDs::updateID = env->GetMethodID(telemetry::telemetryClazz, "update", "()Z");
    telemetry::cachedMethodIDs::addDataID = env->GetMethodID(telemetry::telemetryClazz, "addData", "(Ljava/lang/String;Ljava/lang/Object;)Lorg/firstinspires/ftc/robotcore/external/Telemetry$Item;");;
    telemetry::cachedMethodIDs::addLineID = env->GetMethodID(telemetry::telemetryClazz, "addLine", "(Ljava/lang/String;)Lorg/firstinspires/ftc/robotcore/external/Telemetry$Line;");;


    Gamepad::gamepadClazz = findAndCreateGlobalRef(env, "com/qualcomm/robotcore/hardware/Gamepad");
    jobject localGamepad1 = env->GetObjectField(sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "gamepad1", "Lcom/qualcomm/robotcore/hardware/Gamepad;"));
    gamepads::gamepad1 = std::make_unique<Gamepad>(env->NewGlobalRef(localGamepad1));
    SAFE_DELETE_LOCAL(env, localGamepad1);

    jobject localGamepad2 = env->GetObjectField(sdk::opmode, env->GetFieldID(linearOpMode::linearOpModeClazz, "gamepad2", "Lcom/qualcomm/robotcore/hardware/Gamepad;"));
    gamepads::gamepad2 = std::make_unique<Gamepad>(env->NewGlobalRef(localGamepad2));
    SAFE_DELETE_LOCAL(env, localGamepad2);


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

    Orientation::orientationClazz = findAndCreateGlobalRef(env, "org/firstinspires/ftc/robotcore/external/navigation/Orientation");
    YawPitchRollAngles::yawPitchRollAnglesClazz = findAndCreateGlobalRef(env, "org/firstinspires/ftc/robotcore/external/navigation/YawPitchRollAngles");
    AngleUnit::angleUnitClazz = findAndCreateGlobalRef(env, "org/firstinspires/ftc/robotcore/external/navigation/AngleUnit");
    AngleUnit::DEGREES = env->NewGlobalRef(env->GetStaticObjectField(AngleUnit::angleUnitClazz, env->GetStaticFieldID(AngleUnit::angleUnitClazz,"DEGREES" ,"Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;")));
    AngleUnit::RADIANS = env->NewGlobalRef(env->GetStaticObjectField(AngleUnit::angleUnitClazz, env->GetStaticFieldID(AngleUnit::angleUnitClazz,"RADIANS" ,"Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;")));

}



void deleteSDK(JNIEnv* env)
{
    if (gamepads::gamepad1 != nullptr)
    {
        gamepads::gamepad1.reset();
    }
    if (gamepads::gamepad2 != nullptr)
    {
        gamepads::gamepad2.reset();
    }

    if (sdk::opmode != nullptr) {
        SAFE_DELETE_GLOBAL(env, sdk::opmode);
    }
    if (sdk::hardwareMap != nullptr) {
        SAFE_DELETE_GLOBAL(env, sdk::hardwareMap);
    }
    if (linearOpMode::linearOpModeClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, linearOpMode::linearOpModeClazz);
    }
    if (telemetry::telemetry != nullptr) {
        SAFE_DELETE_GLOBAL(env, telemetry::telemetry);
    }
    if (telemetry::telemetryClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, telemetry::telemetryClazz);
    }
    if (Gamepad::gamepadClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, Gamepad::gamepadClazz);
    }
    if (DcMotorEx::dcMotorExClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, DcMotorEx::dcMotorExClazz);
    }
    if (DcMotorEx::directionClazz)
    {
        SAFE_DELETE_GLOBAL(env, DcMotorEx::directionClazz);
    }
    if (Servo::servoClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, Servo::servoClazz);
    }
    if (LynxModule::lynxModuleClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, LynxModule::lynxModuleClazz);
    }
    if (LynxModule::bulkCachingModeClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, LynxModule::bulkCachingModeClazz);
    }
    if (IMU::imuClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, IMU::imuClazz);
    }
    if (Parameters::IMU::revHubOrientationOnRobotClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, Parameters::IMU::revHubOrientationOnRobotClazz);
    }
    if (Parameters::IMU::parametersClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, Parameters::IMU::parametersClazz);
    }
    if (Parameters::IMU::logoFacingDirectionClazz != nullptr) {
        SAFE_DELETE_GLOBAL(env, Parameters::IMU::logoFacingDirectionClazz);
    }
    if (Parameters::IMU::usbFacingDirectionClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, Parameters::IMU::usbFacingDirectionClazz);
    }
    if (Orientation::orientationClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, Orientation::orientationClazz);
    }
    if (YawPitchRollAngles::yawPitchRollAnglesClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, YawPitchRollAngles::yawPitchRollAnglesClazz);
    }
    if (AngleUnit::angleUnitClazz != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, AngleUnit::angleUnitClazz);
    }
    if (AngleUnit::DEGREES != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, AngleUnit::DEGREES);
    }if (AngleUnit::RADIANS != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, AngleUnit::RADIANS);
    }
}