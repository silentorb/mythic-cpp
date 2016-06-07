#pragma once
#include <android/log.h>
#include <string>
#include <vector>

struct AAssetManager;

void android_initialize_utility(AAssetManager *asset_manager);
void android_load_binary(std::vector<char> &buffer, const std::string &path);

//#define log_info(...) ((void)__android_log_print(ANDROID_LOG_INFO, "mythic", __VA_ARGS__))
//#define log_warning(...) ((void)__android_log_print(ANDROID_LOG_WARN, "mythic", __VA_ARGS__))
