#include "LibLoader.h"

JNIEnv* get_env(JavaVM* jvm)
{
    JNIEnv* env = nullptr;
    jvm->AttachCurrentThread(
            reinterpret_cast<JNIEnv**>(&env),
            nullptr
    );
    return env;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    sdk::jvm = vm;
    JNIEnv* env = get_env(vm);

    const char* filePathBasic = "org/firstinspires/ftc/teamcode/opmodes/";

    int registrySize = 0;

    for (auto registry : Registry::getOpModes())
    {
        ++registrySize;
    }
    LOG_INFO("__________________________ SIZE OF REGISTRY: \"%d\" ________________________________", registrySize);

    if (!Registry::getOpModes().empty())
    {
        for (auto opmodeFunc: Registry::getOpModes()) {
            LOG_INFO("__________________________ OpMode Name: \"%s\" ____________________", opmodeFunc.name);


            char *appendedClazzName = static_cast<char *>(malloc(1024));
            strcpy(appendedClazzName, filePathBasic);
            strcat(appendedClazzName, opmodeFunc.name);

            jclass clazz = env->FindClass(appendedClazzName);
            if (clazz == nullptr)
            {
                LOG_ERROR("_________________Current Opmode Class Could Not Be Found: \"%s\"__________________",opmodeFunc.name);
                continue;
            }

            JNINativeMethod method[] = {opmodeFunc.name, "()V", (void*)opmodeFunc.opmode};

            env->RegisterNatives(clazz, method, sizeof(method) / sizeof(method[0]));
            free(appendedClazzName);
        }
    } else {
        LOG_ERROR("________________________OPMODE REGISTRY EMPTY!_____________________________");
    }


    return JNI_VERSION_1_6;
}
