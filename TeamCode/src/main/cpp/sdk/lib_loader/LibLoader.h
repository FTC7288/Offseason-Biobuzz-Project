#pragma once

#include <jni.h>
#include <android/log.h>
#include <string>
#include "sdk/util/OpmodeRegistry.h"
#include "sdk/util/Util.h"
#include "sdk/util/InitSDK.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved);

