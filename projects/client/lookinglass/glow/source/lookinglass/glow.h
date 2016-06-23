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

#ifdef _MSC_VER
#ifdef GLOW_LIB
#define GLOW_EXPORT __declspec(dllexport)
#else
#define GLOW_EXPORT __declspec(dllimport)
#endif
#else
#define GLOW_EXPORT
#endif

namespace glow {

  GLOW_EXPORT void set_blend(bool value);
  GLOW_EXPORT void set_culling(bool value);
  GLOW_EXPORT void set_depth_test(bool value);
  GLOW_EXPORT void set_depth_write(bool value);
  GLOW_EXPORT void enable_scissor_box(float left, float top, float width, float height);
  GLOW_EXPORT void disable_scissor_box();
  GLOW_EXPORT void set_line_thickness(float value);

}
