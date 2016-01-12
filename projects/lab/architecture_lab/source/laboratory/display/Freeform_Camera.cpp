#include <haft/Event.h>
#include <laboratory/Actions.h>
#include "Freeform_Camera.h"
#include "glm/glm.hpp"
#include "math/utility.h"
#include "haft/Input_State.h"
#include "logger.h"

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
      float move_speed = 45;
      auto &action = event.get_action();
      auto value = event.get_value() * delta;
//      log_info("camera %f %f", value, delta);
//      value *= delta;

      if (&action == Actions::move_left) {
        move_entity(*camera, vec3(1, 0, 0), -value * move_speed);
        return;
      }
      if (&action == Actions::move_right) {
        move_entity(*camera, vec3(1, 0, 0), value * move_speed);
        return;
      }
      if (&action == Actions::move_forward) {
        move_entity(*camera, vec3(0, 1, 0), value * move_speed);
        return;
      }
      if (&action == Actions::move_backward) {
        move_entity(*camera, vec3(0, 1, 0), -value * move_speed);
        return;
      }

      if (&action == Actions::jump) {
        camera->set_position(camera->get_position() + vec3(0, 0, value * move_speed));
        return;
      }
      if (&action == Actions::duck) {
        camera->set_position(camera->get_position() - vec3(0, 0, value * move_speed));
        return;
      }

      if (&action == Actions::look_up) {
        camera->set_orientation(camera->get_orientation() * quat(vec3(-value * 2, 0, 0)));
        return;
      }
      if (&action == Actions::look_down) {
        camera->set_orientation(camera->get_orientation() * quat(vec3(value * 2, 0, 0)));
        return;
      }

      if (&action == Actions::look_left) {
        camera->set_orientation(camera->get_orientation() * quat(vec3(0, 0, -value * 2)));
        return;
      }
      if (&action == Actions::look_right) {
        camera->set_orientation(camera->get_orientation() * quat(vec3(0, 0, value * 2)));
        return;
      }
    }

    void Freeform_Camera::move_entity(Positioned_Oriented &player, vec3 direction, float amount) {
      auto forward = direction * player.get_orientation();
      forward.z = 0;
      glm::normalize(forward);
      player.set_position(player.get_position() + forward * amount);
      //            camera.position.X += v.X;
    }
  }
}