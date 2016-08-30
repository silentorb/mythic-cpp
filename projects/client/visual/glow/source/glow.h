#pragma once

#include "utility.h"
#include <glm/vec4.hpp>

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

  enum class Blend_Factor {
      zero = 0,
      one = 1,
      source_color = 0x0300,
      one_minus_source_color = 0x0301,
      destination_color = 0x0306,
      one_minus_destination_color = 0x0301,
      source_alpha = 0x0302,
      one_minus_source_alpha = 0x0303,
      destination_alpha = 0x0304,
      one_minus_destination_alpha = 0x0305,
      constant_color = 0x8001,
      one_minus_constant_color = 0x8002,
      constant_alpha = 0x8003,
      one_minus_constant_alpha = 0x8004,
      source_alpha_saturate = 0x0308
  };

  struct GLOW_EXPORT Blend_Function {
      Blend_Factor source;
      Blend_Factor destination;
  };

  GLOW_EXPORT bool initialize_desktop();

  GLOW_EXPORT void set_blend(bool value);
  GLOW_EXPORT void set_culling(bool value);
  GLOW_EXPORT void set_depth_test(bool value);
  GLOW_EXPORT void set_depth_write(bool value);
  GLOW_EXPORT void set_line_thickness(float value);
  GLOW_EXPORT void set_blend_function(Blend_Factor source, Blend_Factor destination);

  GLOW_EXPORT void set_clear_color(const glm::vec4 &value);
  GLOW_EXPORT const glm::vec4 &get_clear_color();

  GLOW_EXPORT inline void set_blend_function(Blend_Function blend_function) {
    set_blend_function(blend_function.source, blend_function.destination);
  }

  GLOW_EXPORT void enable_scissor_box(float left, float top, float width, float height);
  GLOW_EXPORT void disable_scissor_box();
}
