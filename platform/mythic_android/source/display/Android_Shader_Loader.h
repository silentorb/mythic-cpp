#pragma once

#include<string>
#include "lookinglass/shading/Shader_Loader.h"
#include "../android_native_app_glue.h"

using namespace std;

class Android_Shader_Loader : public lookinglass::shading::Shader_Loader {

    AAssetManager *asset_manager;
public:

    Android_Shader_Loader(AAssetManager *asset_manager);
    virtual string load(string path);

};