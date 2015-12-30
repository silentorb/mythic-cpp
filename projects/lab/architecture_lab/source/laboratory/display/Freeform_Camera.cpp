#include "Freeform_Camera.h"

namespace laboratory {
  namespace display {

    Freeform_Camera::Freeform_Camera(Viewport & viewport)
      : camera(new Camera()) {
viewport.set_camera(*camera);
    }

    void Freeform_Camera::update(float delta, Client &client) {

    }
  }
}