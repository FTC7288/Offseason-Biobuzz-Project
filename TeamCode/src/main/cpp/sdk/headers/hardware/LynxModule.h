#pragma once

#include "sdk/util/Util.h"

class LynxModule
{
private:
    jobject lynxModule = nullptr;

    jmethodID setBulkCachingModeID = nullptr;

    const char* toString[3] = {"AUTO", "MANUAL", "OFF"};


public:
    enum BulkCachingMode
    {
        AUTO,
        MANUAL,
        OFF
    };

    inline static jclass lynxModuleClazz = nullptr;
    inline static jclass bulkCachingModeClazz = nullptr;



    explicit LynxModule(const char* lynxModlueName);

    ~LynxModule();

    void setBulkCachingMode(BulkCachingMode bulkCachingMode);

};
