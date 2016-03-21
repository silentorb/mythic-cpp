#include "lookinglass/Glass.h"
#include <lookinglass/glow/Capabilities.h>
#include "lookinglass/glow.h"
#include "modeling/Mesh_Data.h"
#include "perspective/Viewport.h"

namespace lookinglass {

  Glass *glass_instance;

  Glass::Glass(Viewport &viewport) :
    capabilities(capabilities), viewport(&viewport) {
    glass_instance = this;
  }

  void Glass::draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method) {
    glBindVertexArray(mesh.get_vao());
    glow::check_error("binding mesh.");

    auto mode = draw_method == Draw_Method::triangles
                ? GL_TRIANGLE_FAN
                : GL_LINE_STRIP;

    if (glow::Capabilities::multidraw()) {
      // The preprocessor is needed or this will fail to compile on some platforms.
#ifdef glMultiDrawArrays
      glMultiDrawArrays(mode, mesh.get_offsets(), mesh.get_counts(), mesh.get_polygon_count());
#endif
    }
    else {
      if (draw_method == Draw_Method::lines || mesh.supports_lines()) {
        for (int i = 0; i < mesh.get_polygon_count(); ++i) {
          glDrawArrays(mode, mesh.get_offsets()[i], mesh.get_counts()[i]);
        }
      }
      else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.get_ebo());
        glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_SHORT, nullptr);
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

  const ivec2 &Glass::get_viewport_dimensions() const {
    return viewport->get_dimensions();
  }

  Glass &Glass::get_instance() {
    return *glass_instance;
  }
}