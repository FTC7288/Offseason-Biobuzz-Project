#pragma once

#include "sdk/util/Util.h"

class LynxModule
{
private:
    jobject lynxModule = nullptr;

    jmethodID setBulkCachingModeID = nullptr;

    const char* toString[3] = {"AUTO", "MANUAL", "OFF"};


public:
    struct BulkCachingMode
    {
        inline static jclass bulkCachingModeClazz = nullptr;

        inline static jobject AUTO = nullptr;
        inline static jobject MANUAL = nullptr;
        inline static jobject OFF = nullptr;
    };

    inline static jclass lynxModuleClazz = nullptr;



    explicit LynxModule(const char* lynxModlueName);

    ~LynxModule();

    void setBulkCachingMode(jobject* bulkCachingMode);

};
