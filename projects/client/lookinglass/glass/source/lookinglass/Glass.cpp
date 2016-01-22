#include "lookinglass/Glass.h"
#include <lookinglass/glow/Capabilities.h>
#include "lookinglass/glow.h"
#include "lookinglass/modeling/Mesh_Data.h"
#include "lookinglass/perspective/Viewport.h"

namespace lookinglass {
  Glass::Glass(const glow::Capabilities &capabilities, Viewport &viewport) :
    capabilities(capabilities), viewport(&viewport) {

  }

  void Glass::draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method) {
    glBindVertexArray(mesh.get_vao());
    glow::check_error("binding mesh.");

    auto mode = draw_method == Draw_Method::triangles
                ? GL_TRIANGLE_FAN
                : GL_LINE_STRIP;

//		if (0) {
    if (capabilities.multidraw) {
#ifdef glMultiDrawArrays
      glMultiDrawArrays(mode, mesh.get_offsets(), mesh.get_counts(), mesh.get_polygon_count());
#endif
    }
    else {
      for (int i = 0; i < mesh.get_polygon_count(); ++i) {
        glDrawArrays(mode, mesh.get_offsets()[i], mesh.get_counts()[i]);
      }
    }

    glow::check_error("drawing mesh");
  }

  Viewport &Glass::get_viewport() const {
    return *viewport;
  }

  void Glass::set_viewport(Viewport &viewport) {
    this->viewport = &viewport;
  }

  int Glass::get_viewport_width() const {
    return viewport->get_width();
  }

  int Glass::get_viewport_height() const {
    return viewport->get_height();
  }
}