#include "lookinglass/Glass.h"
#include <lookinglass/glow/Capabilities.h>
#include "lookinglass/glow.h"

namespace lookinglass {
  Glass::Glass(glow::Capabilities &capabilities) :
    capabilities(capabilities) {

  }

  void Glass::draw_mesh(Mesh_Data &mesh, Draw_Method draw_method) {
    glBindVertexArray(mesh.vao);
    glow::check_error("binding mesh.");

    auto mode = draw_method == Draw_Method::triangles
                ? GL_TRIANGLE_FAN
                : GL_LINE_STRIP;

    if (capabilities.multidraw) {
      glMultiDrawArrays(mode, mesh.offsets, mesh.counts, mesh.polygon_count);
    }
    else {
      for (int i = 0; i < mesh.polygon_count; ++i) {
        glDrawArrays(mode, mesh.offsets[i], mesh.counts[i]);
      }
    }

    glow::check_error("drawing mesh");
  }
}