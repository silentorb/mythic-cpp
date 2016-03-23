#include <lookinglass/glow.h>
#include "Particle_Effect.h"

namespace scenery {

  void Particle_Effect::activate() {
    Program::activate();
    model_property.set(glm::mat4(1));
    glow::set_blend(true);
    glow::set_depth_test(false);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  }
}