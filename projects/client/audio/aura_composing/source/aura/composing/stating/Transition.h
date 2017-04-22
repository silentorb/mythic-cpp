#pragma once

#include "State.h"
#include <memory>

namespace aura {
  namespace composing {
    namespace stating {

      template<typename Sound, typename Event=sequencing::Note>
      class Transition {
      public:
          virtual State<Sound, Event> &get_next_state(State<Sound, Event> &current_state) = 0;
      };

      template<typename Sound, typename Event=sequencing::Note>
      using Transition_Pointer = std::unique_ptr<Transition<Sound, Event>>;
    }
  }
}