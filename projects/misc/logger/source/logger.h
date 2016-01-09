#pragma once

//typedef void (*Logger_Function)(const char*,...);
//
////Logger_Function log_info;
////Logger_Function log_warning;

#if __ANDROID__
#include <android/log.h>
#define log_info(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define log_warning(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define log_error(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
#else
#include "dllexport.h"
MYTHIC_EXPORT void log_info(const char *,...);
MYTHIC_EXPORT void log_warning(const char *,...);
MYTHIC_EXPORT void log_error(const char *,...);
#endif