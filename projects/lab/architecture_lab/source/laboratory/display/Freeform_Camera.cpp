#include "Freeform_Camera.h"
#include "glm/glm.hpp"
#include "math/utility.h"

using namespace glm;

namespace laboratory {
  namespace display {

    Freeform_Camera::Freeform_Camera(Viewport &viewport)
      : camera(new Camera()) {
      camera->set_position(vec3(0, 20, 30));
      camera->set_orientation(quat(vec3(0, -M_PI_4 * 0.7f, 0)));
      viewport.set_camera(*camera);
    }

    void Freeform_Camera::update(float delta, Client &client) {

    }
  }
}