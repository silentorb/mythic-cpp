#include <haft/Event.h>
#include <laboratory/Actions.h>
#include "Freeform_Camera.h"
#include "glm/glm.hpp"
#include "math/utility.h"
#include "haft/Input_State.h"

using namespace glm;

namespace laboratory {
  namespace display {

    Freeform_Camera::Freeform_Camera(Viewport &viewport)
      : camera(new Camera()) {
      camera->set_position(vec3(0, -20, 6));
      camera->set_orientation(quat(vec3(M_PI_4 * 0.2f, 0, 0)));
      viewport.set_camera(*camera);
    }

    void Freeform_Camera::update(float delta, Client &client) {
      auto &state = client.get_current_input_state();
      for (auto it = state.events_begin(); it != state.events_end(); ++it) {
        process_event(*it->get(), delta);
      }
    }

    void Freeform_Camera::process_event(haft::Event &event, float delta) {
      auto &action = event.get_action();
      if (&action == Actions::move_left) {
        camera->set_position(camera->get_position() + vec3(-1, 0, 0));
        return;
      }

    }
  }
}