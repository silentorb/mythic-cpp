#include "Image_Effect.h"

namespace drawing {
  Image_Effect::Image_Effect(shading::Program &program, modeling::Simple_Mesh &mesh) :
    Effect(program),
    mesh(mesh) {

  }

  void Image_Effect::render(const mat4 &transform) {
    mesh.render();
  }
}