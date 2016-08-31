#include "utility.h"
#include "glow.h"

namespace shading {

  void set_opacity_support(bool value){
    if (value) {
//      glow::set_culling(false);
      glow::set_blend(true);
    }
    else {
      glow::set_culling(true);
      glow::set_blend(false);
    }
  }
}

