#include <glaze/rendering/general.h>
#include "GL_Desktop_Brush.h"

using namespace glaze::definition;

namespace glaze {
  namespace brushes {

    using namespace rendering;

    const Donut GL_Desktop_Brush(const Material &material) {
      Donut donut;
      string vertex_code;
//      for (auto &input: material.get_inputs()) {
//        vertex_code += "in " + input.get_type().get_name() + " " + input.get_name() + ";\n";
//      }
      vertex_code += declare_variables("uniform ", material.get_uniforms());
      vertex_code += "\n";
      vertex_code += declare_variables("in ", material.get_inputs());
      donut.vertex = vertex_code;
      return donut;
    }
  }
}