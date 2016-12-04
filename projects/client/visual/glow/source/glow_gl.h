#pragma once

#if _MSC_VER
#define APIENTRY __stdcall
#include <glad/glad.h>
//#include <gl_core_4_4.h>

#elif __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif __ANDROID__
#include "android-gl.h"
#else

#include <gl_core_4_4.h>

#endif
