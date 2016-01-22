#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include "lookinglass/glow.h"


namespace lookinglass {
  namespace perspective {
    Viewport *active_viewport = NULL;

    Viewport::Viewport(Mist<Viewport_Data> &mist, int width, int height, int left, int top) :
      mist(mist),
      dimensions(ivec2(width, height)),
      left(left),
      top(top),
      camera(nullptr) {
      set_projection();
    }

    void Viewport::set_projection() {
      projection = glm::perspective(glm::radians(45.0f), get_aspect_ratio(), 0.1f, 600.0f);
    }

    Viewport *Viewport::get_active_viewport() {
      return active_viewport;
    }

    void Viewport::activate() {
      if (active_viewport == this)
        return;

      active_viewport = this;

      glViewport(left, top, dimensions.x, dimensions.y);
      update_device();
    }

    void Viewport::update_device() {
      if (camera == nullptr)
        return;

      auto data = Viewport_Data();
      data.view = camera->get_view_matrix();
      data.projection = projection;
      data.camera_direction = camera->get_orientation() * vec3(0, 1, 0);
      mist.update(&data);
    }
  }
}