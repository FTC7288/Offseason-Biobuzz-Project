#pragma once

#include "sdk/util/Util.h"
#include <any>

namespace telemetry
{
    extern jclass telemetryClazz;
    extern jobject telemetry;

    namespace cachedMethodIDs
    {
        extern jmethodID updateID;
        extern jmethodID addDataID;
        extern jmethodID addLineID;
    }

    bool update();

    template <typename T>
    void addData(const char* caption, const std::any &data);

    void addLine(const char* caption);
}