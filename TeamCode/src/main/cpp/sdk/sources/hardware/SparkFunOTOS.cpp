#include "sdk/headers/hardware/SparkFunOTOS.h"

SparkFunOTOS::SparkFunOTOS(const char *name)
{
    JNIEnv* env = getEnv();

    jstring jname = env->NewStringUTF(name);
    sparksFunOtos = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, sparksFunOtosClazz, jname);
    env->DeleteLocalRef(jname);

    beginID = env->GetMethodID(sparksFunOtosClazz, "begin", "()Z");
    setOffsetID = env->GetMethodID(sparksFunOtosClazz, "setOffset", "(Lcom/qualcomm/hardware/sparkfun/SparkFunOTOS$Pose2D;)V");
    getPositionID = env->GetMethodID(sparksFunOtosClazz, "getPosition", "()Lcom/qualcomm/hardware/sparkfun/SparkFunOTOS$Pose2D;");
    setPositionID = env->GetMethodID(sparksFunOtosClazz, "setPosition", "(Lcom/qualcomm/hardware/sparkfun/SparkFunOTOS$Pose2D;)V");
    setAngularUnitID = env->GetMethodID(sparksFunOtosClazz, "setAngularUnit", "(Lorg/firstinspires/ftc/robotcore/external/navigation/AngleUnit;)V");
    setLinearUnitID = env->GetMethodID(sparksFunOtosClazz, "setLinearUnit", "(Lorg/firstinspires/ftc/robotcore/external/navigation/DistanceUnit;)V");
    setAngularScalarID = env->GetMethodID(sparksFunOtosClazz, "setAngularScalar", "(D)Z");
    setLinearScalarID = env->GetMethodID(sparksFunOtosClazz, "setLinearScalar", "(D)Z");

    pose2D = *new Pose2D();

    LOG_INFO("----- Creating SparkFunOTOS object '%s' -----", name);
}

SparkFunOTOS::~SparkFunOTOS()
{
    JNIEnv *env = getEnv();
    if (globalPose2D != nullptr)
    {
        SAFE_DELETE_GLOBAL(env, globalPose2D,__LINE__,__FILE_NAME__);
    }
    if (sparksFunOtos != nullptr)
    {
        SAFE_DELETE_LOCAL(env,sparksFunOtos);
    }
}

bool SparkFunOTOS::begin()
{
    JNIEnv* env = getEnv();
    return env->CallBooleanMethod(sparksFunOtos, beginID);
}

void SparkFunOTOS::setPosition(Pose2D *pose)
{
    JNIEnv* env = getEnv();
    jmethodID jposeObj = env->GetMethodID(Pose2D::pose2DClazz, "<init>", "(DDD)V");
    jobject jpose = env->NewObject(Pose2D::pose2DClazz, jposeObj, pose->x, pose->y, pose->h);
    env->CallVoidMethod(sparksFunOtos, setPositionID, jpose);
    env->DeleteLocalRef(jpose);
}

const Pose2D* SparkFunOTOS::getPosition()
{
    JNIEnv *env = getEnv();

    jobject jPose2D = env->CallObjectMethod(sparksFunOtos, getPositionID);
    globalPose2D = env->NewGlobalRef(jPose2D);


    pose2D.x = env->GetDoubleField(jPose2D, env->GetFieldID(Pose2D::pose2DClazz, "x", "D"));
    pose2D.y = env->GetDoubleField(jPose2D, env->GetFieldID(Pose2D::pose2DClazz, "y", "D"));
    pose2D.h = env->GetDoubleField(jPose2D, env->GetFieldID(Pose2D::pose2DClazz, "h", "D"));

    env->DeleteLocalRef(jPose2D);
    return &pose2D;
}

void SparkFunOTOS::setOffset(Pose2D *pose)
{
    JNIEnv* env = getEnv();
    jmethodID jposeObj = env->GetMethodID(Pose2D::pose2DClazz, "<init>", "(DDD)V");
    jobject jpose = env->NewObject(Pose2D::pose2DClazz, jposeObj, pose->x, pose->y, pose->h);
    env->CallVoidMethod(sparksFunOtos, setPositionID, jpose);
    env->DeleteLocalRef(jpose);
}

void SparkFunOTOS::setAngularUnit(jobject *angleUnit)
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(sparksFunOtos, setAngularUnitID, *angleUnit);
}

void SparkFunOTOS::setLinearUnit(jobject *distanceUnit)
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(sparksFunOtos, setLinearUnitID, *distanceUnit);
}

bool SparkFunOTOS::setAngularScalar(double scalar)
{
    JNIEnv* env = getEnv();
    return env->CallBooleanMethod(sparksFunOtos, setAngularScalarID, scalar);
}

bool SparkFunOTOS::setLinearScalar(double scalar)
{
    JNIEnv* env = getEnv();
    return env->CallBooleanMethod(sparksFunOtos, setLinearScalarID, scalar);;
}
