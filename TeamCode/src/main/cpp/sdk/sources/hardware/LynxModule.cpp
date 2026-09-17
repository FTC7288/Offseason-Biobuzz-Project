#include "sdk/headers/hardware/LynxModule.h"

LynxModule::LynxModule(const char *lynxModlueName)
{
    JNIEnv* env = getEnv();

    jstring jdcMotorName = env->NewStringUTF(lynxModlueName);
    lynxModule = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, lynxModuleClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setBulkCachingModeID = env->GetMethodID(lynxModuleClazz, "setBulkCachingMode", "(Lcom/qualcomm/hardware/lynx/LynxModule$BulkCachingMode;)V");
}

LynxModule::~LynxModule()
{
    JNIEnv* env = getEnv();

    if (lynxModuleClazz)
    {
        env->DeleteGlobalRef(lynxModuleClazz);
        lynxModuleClazz = nullptr;
    }
    if (bulkCachingModeClazz)
    {
        env->DeleteLocalRef(bulkCachingModeClazz);
        bulkCachingModeClazz = nullptr;
    }
    if (lynxModule)
    {
        env->DeleteLocalRef(lynxModule);
        lynxModule = nullptr;
    }
}

void LynxModule::setBulkCachingMode(LynxModule::BulkCachingMode bulkCachingMode)
{
    JNIEnv* env = getEnv();

    jobject jbulkCachingMode = env->GetStaticObjectField(bulkCachingModeClazz, env->GetStaticFieldID(bulkCachingModeClazz,toString[bulkCachingMode],"Lcom/qualcomm/hardware/lynx/LynxModule$BulkCachingMode;"));
    env->CallVoidMethod(lynxModule, setBulkCachingModeID, jbulkCachingMode);
    env->DeleteLocalRef(jbulkCachingMode);
}
