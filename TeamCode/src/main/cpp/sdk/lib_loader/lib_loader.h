#pragma once

#include <jni.h>
#include <android/log.h>
#include <string>
#include "sdk/util/opmodeRegistry.h"
#include "sdk/util/util.h"
#include "sdk/util/initSDK.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved);

