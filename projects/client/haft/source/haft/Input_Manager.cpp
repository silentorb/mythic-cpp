#include "Input_Manager.h"

namespace haft {

  Input_Manager::Input_Manager() :
    config(new Input_Configuration()),
    source(nullptr),
    current_state(new Input_State()),
    previous_state(new Input_State()) {
  }

  void Input_Manager::update() {
    if (!source)
      throw runtime_error("Input source not set.");

    previous_state = move(current_state);
    current_state = unique_ptr<Input_State>(source->get_input_state());

    current_state->set_previous(previous_state.get());
    previous_state->set_previous(nullptr);

    for (auto &interpreter: gesture_interpreters) {
      interpreter->interpret(*current_state, *current_state);
    }
  }

  void Input_Manager::add_input_source(Input_Source *new_source) {
    if (source)
      throw runtime_error("Multiple input sources not yet implemented.");

    source = unique_ptr<Input_Source>(new_source);
  }
}
