#pragma once
#include "dllexport.h"

#if _MSC_VER
#include <glad/glad.h>
#elif __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif __ANDROID__
#include "android-gl.h"
#else
#include <gl_core_4_4.h>
#endif
#include "utility.h"
