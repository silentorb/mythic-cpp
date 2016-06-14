#include <SDL2/SDL_mouse.h>
#include "Desktop_Input.h"
#include "Device_Type.h"
#include "Gamepad_Trigger.h"

const float gamepad_min_threshold = 0.25f;

namespace desktop {
  Desktop_Input::Desktop_Input(Input_Configuration &config) : Input_Source(config) {
    initialize_keyboard();
    initialize_mouse();
    initialize_gamepad();
  }

  void Desktop_Input::initialize_keyboard() {
    keyboard = new Device("keyboard");
    config.add_device(keyboard);
  }

  void Desktop_Input::initialize_mouse() {
    mouse = new Device("mouse", {
      new Trigger("Left", 1),
      new Trigger("Right", 2),
      new Trigger("Middle", 3),
    });
    config.add_device(mouse);
  }

  void Desktop_Input::initialize_gamepad() {
    gamepad = new Device("gamepad", {
      new Trigger("A", Gamepad_Trigger::A),
      new Trigger("B", Gamepad_Trigger::B),
      new Trigger("X", Gamepad_Trigger::X),
      new Trigger("Y", Gamepad_Trigger::Y),
      new Trigger("Back", Gamepad_Trigger::Back),
      new Trigger("Guide", Gamepad_Trigger::Guide),
      new Trigger("Start", Gamepad_Trigger::Start),
      new Trigger("LS", Gamepad_Trigger::LS),
      new Trigger("RS", Gamepad_Trigger::RS),
      new Trigger("LShoulder", Gamepad_Trigger::LShoulder),
      new Trigger("RShoulder", Gamepad_Trigger::RShoulder),
      new Trigger("LS_Up", Gamepad_Trigger::LS_Up),
      new Trigger("LS_Down", Gamepad_Trigger::LS_Down),
      new Trigger("LS_Left", Gamepad_Trigger::LS_Left),
      new Trigger("LS_Right", Gamepad_Trigger::LS_Right),
      new Trigger("RS_Up", Gamepad_Trigger::RS_Up),
      new Trigger("RS_Down", Gamepad_Trigger::RS_Down),
      new Trigger("RS_Left", Gamepad_Trigger::RS_Left),
      new Trigger("RS_Right", Gamepad_Trigger::RS_Right),
      new Trigger("LTrigger", Gamepad_Trigger::LTrigger),
      new Trigger("RTrigger", Gamepad_Trigger::RTrigger)
    });

    config.add_device(gamepad);
  }

  Input_State *Desktop_Input::get_input_state() {
    auto state = new Input_State();
    update_gamepad(*state);
    update_keyboard(*state);
    update_mouse(*state);
    return state;
  }

  void Desktop_Input::update_keyboard(Input_State &state) {

  }

  void Desktop_Input::update_mouse(Input_State &state) {
    ivec2 point;
    auto buttons = SDL_GetMouseState(&point.x, &point.y);
    state.set_position(point);

    for (int i = 0; i <= 2; i++) {
      auto &trigger = mouse->get_trigger(i);
      if (trigger.get_action()) {
        if (trigger.get_id() < 4 && buttons & trigger.get_id())
          state.add_event(*trigger.get_action());
      }
    }

    for (int i = 1; i <= 3; i++) {
      if (buttons & i) {
        if (previous_buttons & i) {
          state.add_gesture(Gesture_Type::move, point);
        }
        else {
          state.add_gesture(Gesture_Type::down, point);
        }
      }
      else if (previous_buttons & i == 1) {
        state.add_gesture(Gesture_Type::up, point);
      }
    }

    previous_buttons = buttons;
  }

  void Desktop_Input::update_gamepad(Input_State &state) {
    auto controller = gamepad_manager.get_controller();
    if (!controller)
      return;

    for (int i = 0; i <= Gamepad_Trigger::RShoulder; i++) {
      auto &trigger = gamepad->get_trigger(i);
      if (trigger.get_action()) {
        if (SDL_GameControllerGetButton(controller, (SDL_GameControllerButton) i) != 0) {
          state.add_event(*trigger.get_action());
        }
      }
    }

    check_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX),
               gamepad, Gamepad_Trigger::LS_Left, state);

    check_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY),
               gamepad, Gamepad_Trigger::LS_Up, state);

    check_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX),
               gamepad, Gamepad_Trigger::RS_Left, state);

    check_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY),
               gamepad, Gamepad_Trigger::RS_Up, state);

    check_positive_direction(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.5,
                             gamepad->get_trigger(Gamepad_Trigger::LTrigger), state);

    check_positive_direction(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.5,
                             gamepad->get_trigger(Gamepad_Trigger::RTrigger), state);
  }

  void Desktop_Input::check_axis(double value, const Device *device, int first_trigger, Input_State &state) {
    value /= 32767.5;
    check_negative_direction(value, device->get_trigger(first_trigger), state);
    check_positive_direction(value, device->get_trigger(first_trigger + 1), state);
  }

  void Desktop_Input::check_negative_direction(double value, Trigger &trigger, Input_State &state) {
    if (value < -gamepad_min_threshold && trigger.get_action()) {
      state.add_event(*trigger.get_action(), -value);
    }
  }

  void Desktop_Input::check_positive_direction(double value, Trigger &trigger, Input_State &state) {
    if (value > gamepad_min_threshold && trigger.get_action()) {
      state.add_event(*trigger.get_action(), value);
    }
  }
}