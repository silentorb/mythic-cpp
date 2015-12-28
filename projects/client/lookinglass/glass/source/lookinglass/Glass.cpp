#include "lookinglass/Glass.h"
#include <lookinglass/glow/Capabilities.h>
#include "lookinglass/glow.h"
#include "lookinglass/modeling/Mesh_Data.h"

namespace lookinglass {
  Glass::Glass(glow::Capabilities &capabilities) :
    capabilities(capabilities) {

  }

  void Glass::draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method) {
    glBindVertexArray(mesh.get_vao());
    glow::check_error("binding mesh.");

    auto mode = draw_method == Draw_Method::triangles
                ? GL_TRIANGLE_FAN
                : GL_LINE_STRIP;

    if (capabilities.multidraw) {
      glMultiDrawArrays(mode, mesh.get_offsets(), mesh.get_counts(), mesh.get_polygon_count());
    }
    else {
      for (int i = 0; i < mesh.get_polygon_count(); ++i) {
        glDrawArrays(mode, mesh.get_offsets()[i], mesh.get_counts()[i]);
      }
    }

    glow::check_error("drawing mesh");
  }
}