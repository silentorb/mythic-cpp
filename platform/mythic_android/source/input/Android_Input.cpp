#include "Android_Input.h"
//#include "Device_Type.h"
//#include "Surface_Trigger.h"
#include "logger.h"
#include "Surface_Trigger.h"

const float gamepad_min_threshold = 0.25f;

Android_Input::Android_Input(Input_Configuration &config) : Input_Source(config) {
//    initialize_keyboard();
  initialize_mouse();
  initialize_gamepad();
  initialize_surface();
  last_position = vec2();
  current_position = vec2();
  motion_finished = false;
  next_state = new Input_State();
}

void Android_Input::initialize_surface() {
  surface = new Device("surface", {
    new Trigger("swipe", Surface_Trigger::swipe),
    new Trigger("swipe_left", Surface_Trigger::swipe_left),
    new Trigger("swipe_right", Surface_Trigger::swipe_right),
    new Trigger("swipe_up", Surface_Trigger::swipe_down),
    new Trigger("swipe_down", Surface_Trigger::swipe_up)
  });

  config.add_device(surface);
}

void Android_Input::initialize_mouse() {
  mouse = new Device("mouse", {
    new Trigger("Left", 1),
    new Trigger("Right", 2),
    new Trigger("Middle", 3),
  });
  config.add_device(mouse);
}

Input_State *Android_Input::get_input_state() {
  auto result = next_state;
  next_state = new Input_State();

//  next_state = new Input_State();
  auto offset = current_position - last_position;
  if (offset.x != 0 || offset.y != 0) {
//    log_info("offset %f, %f", offset.x, offset.y);

    check_axis(offset.x, surface, Surface_Trigger::swipe_left, *result);
    check_axis(offset.y, surface, Surface_Trigger::swipe_up, *result);

    if (motion_finished) {
      last_position = current_position = vec2();
    }
    else {
      last_position = current_position;
    }
  }
  return result;
  //  update_gamepad(*state);
//    update_keyboard(*state);
//    update_mouse(*state);
}

void Android_Input::initialize_gamepad() {
  gamepad = new Device("gamepad");

  config.add_device(gamepad);
}

void Android_Input::update_gamepad(Input_State &state) {

}

vec2 get_event_position(AInputEvent *event) {
  return vec2(
    AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_X, 0),
    AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Y, 0)
  );
}

void Android_Input::process_input(AInputEvent *event) {
  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    auto action_type = AMotionEvent_getAction(event);
    if (action_type == AMOTION_EVENT_ACTION_DOWN) {
      last_position = current_position = get_event_position(event);
//      log_info("AMOTION_EVENT_ACTION_DOWN %f, %f", last_position.x, last_position.y);
      motion_finished = false;
      next_state->add_gesture(Gesture_Type::down, current_position);
    }
    else if (action_type == AMOTION_EVENT_ACTION_MOVE) {
      current_position = get_event_position(event);
      next_state->add_gesture(Gesture_Type::move, current_position);
//      log_info("AMOTION_EVENT_ACTION_MOVE %f, %f", current_position.x, current_position.y);
    }
    else if (action_type == AMOTION_EVENT_ACTION_UP) {
      current_position = get_event_position(event);
      log_info("AMOTION_EVENT_ACTION_UP %f, %f", current_position.x, current_position.y);
      next_state->add_gesture(Gesture_Type::up, current_position);
      single_click(current_position.x, current_position.y);
      motion_finished = true;
    }
  }
}

void Android_Input::check_axis(double value, const Device *device, int first_trigger, Input_State &state) {
  value *= 0.3;
  check_negative_direction(value, device->get_trigger(first_trigger), state);
  check_positive_direction(value, device->get_trigger(first_trigger + 1), state);
}

void Android_Input::check_negative_direction(double value, Trigger &trigger, Input_State &state) {
  if (value < 0 && trigger.get_action()) {
    state.add_event(*trigger.get_action(), -value);
//    log_info("value1 %f %s", -value,trigger.get_name().c_str());
  }
}

void Android_Input::check_positive_direction(double value, Trigger &trigger, Input_State &state) {
  if (value > 0 && trigger.get_action()) {
    state.add_event(*trigger.get_action(), value);
//    log_info("value2 %f %s", value,trigger.get_name().c_str());
  }
}

void Android_Input::single_click(int x, int y) {
  auto &trigger = mouse->get_trigger(0);
  auto action = trigger.get_action();
  if (action)
    next_state->add_event(*action);

  next_state->set_position(glm::ivec2(x, y));
}
