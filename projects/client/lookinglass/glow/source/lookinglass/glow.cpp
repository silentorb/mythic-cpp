#include "glow.h"

namespace glow {

  namespace cache {
    bool blend = false;
    bool culling = false;
    bool depth_test = false;
    bool depth_write = false;
    bool scissor_box = false;
    float line_width = 1;
  }

  void toggle(GLenum setting, bool value) {
    if (value)
      glEnable(setting);
    else
      glDisable(setting);

  }

  void set_depth_test(bool value) {
    if (cache::depth_test == value)
      return;

    cache::depth_test = value;
    toggle(GL_DEPTH_TEST, value);
  }

  void set_depth_write(bool value) {
    if (cache::depth_write == value)
      return;

    cache::depth_write = value;
    glDepthMask(value);
  }

  void set_culling(bool value) {
    if (cache::culling == value)
      return;

    cache::culling = value;
    toggle(GL_CULL_FACE, value);
  }

  void set_blend(bool value) {
    if (cache::blend == value)
      return;

    cache::blend = value;
    toggle(GL_BLEND, value);
  }

  void enable_scissor_box(float left, float top, float width, float height) {
    if (!cache::scissor_box)
      glEnable(GL_SCISSOR_TEST);

    cache::scissor_box = true;
    glScissor(left, top, width, height);
  }

  void disable_scissor_box() {
    if (!cache::scissor_box)
      return;

    cache::scissor_box = false;
    glDisable(GL_SCISSOR_TEST);
  }

  void set_line_thickness(float value) {
    if (cache::line_width == value)
      return;

    cache::line_width = value;
    glLineWidth(value);
  }

}

