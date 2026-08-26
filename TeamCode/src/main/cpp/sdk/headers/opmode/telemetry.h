#pragma once

#include "sdk/util/util.h"

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

    void addData(const char* caption, const char* data);

    void addLine(const char* caption);
}