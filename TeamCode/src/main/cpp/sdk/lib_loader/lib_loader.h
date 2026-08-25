#pragma once

#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <string>
#include "sdk/util/opmodeRegistry.h"
#include "sdk/util/util.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved);

