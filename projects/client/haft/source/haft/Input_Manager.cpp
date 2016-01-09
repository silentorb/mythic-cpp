#include "Input_Manager.h"

namespace haft {

  Input_Manager::Input_Manager(Input_Source *source)
    : source(source),
      current_state(new Input_State()),
      previous_state(nullptr) {
  }

  void Input_Manager::update() {
    previous_state = move(current_state);
    current_state = unique_ptr<Input_State>(source->get_input_state());
    for (auto &interpreter: gesture_interpreters) {
      interpreter->interpret(current_state->gestures, *current_state);
    }
  }
}
