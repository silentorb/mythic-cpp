#include "glow.h"

namespace glow {

  namespace cache {
    bool blend = false;
    bool culling = false;
    bool depth_test = false;
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
//    glDepthMask(value);
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
}

