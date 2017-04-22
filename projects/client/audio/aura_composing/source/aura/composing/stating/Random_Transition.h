#pragma once

#include <randomly/Dice.h>
#include "Transition.h"

namespace aura {
  namespace composing {
    namespace stating {

      template<typename Sound, typename Event=sequencing::Note>
      class Random_Transition : public Transition<Sound, Event> {
          randomly::Dice &dice;
          std::vector<State<Sound, Event> *> states;

      public:
          Random_Transition(randomly::Dice &dice, std::initializer_list<State<Sound, Event> *> states) :
            dice(dice), states(states) {
          }

          State<Sound, Event> &get_next_state(State<Sound, Event> &current_state) override {
            return *dice.get_item(states);
          }
      };
    }
  }
}