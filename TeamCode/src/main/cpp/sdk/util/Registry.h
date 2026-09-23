#pragma once

#include <vector>

typedef void (*DesiredOpMode)(JNIEnv*, jobject);

struct RegisteredOpMode
{
    const char* name;
    DesiredOpMode opmode;
};


class Registry
{
public:
    static std::vector<RegisteredOpMode>& getOpModes()
    {
        static std::vector<RegisteredOpMode> opmodes;
        return opmodes;
    }

    static void registerOpMode(const char* name, DesiredOpMode opmode)
    {
        getOpModes().push_back({name, opmode});
    }
};

#define TeleOp(name, group)                                                                    \
    static void __attribute__((constructor)) _register_##name()                         \
    {                                                                                   \
        __android_log_print(ANDROID_LOG_INFO, "sdk_loader", "Registering: %s", #name);  \
        Registry::registerOpMode(#name, name);                                    \
    }

#define Autonomous(name, group)                                                                \
    static void __attribute__((constructor)) _register_##name()                         \
    {                                                                                   \
        __android_log_print(ANDROID_LOG_INFO, "sdk_loader", "Registering: %s", #name);  \
        Registry::registerOpMode(#name, name);                                    \
    }