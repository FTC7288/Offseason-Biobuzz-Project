#include "sdk/headers/hardware/LynxModule.h"

LynxModule::LynxModule(const char *lynxModlueName)
{
    JNIEnv* env = getEnv();

    jstring jdcMotorName = env->NewStringUTF(lynxModlueName);
    lynxModule = env->CallObjectMethod(sdk::hardwareMap,sdk::getID, lynxModuleClazz, jdcMotorName);
    env->DeleteLocalRef(jdcMotorName);

    setBulkCachingModeID = env->GetMethodID(lynxModuleClazz, "setBulkCachingMode", "(Lcom/qualcomm/hardware/lynx/LynxModule$BulkCachingMode;)V");

    LOG_INFO("----- Creating LynxModuleName object '%s' -----", lynxModlueName);
}

LynxModule::~LynxModule()
{
    JNIEnv* env = getEnv();

    if (lynxModule)
    {
        SAFE_DELETE_LOCAL(env,lynxModule);
    }
}

void LynxModule::setBulkCachingMode(jobject* bulkCachingMode)
{
    JNIEnv* env = getEnv();
    env->CallVoidMethod(lynxModule, setBulkCachingModeID, *bulkCachingMode);
}
