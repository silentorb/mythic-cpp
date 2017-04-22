#pragma once

#include <aura/composing/sectioned/Section.h>
#include <aura/composing/sectioned/Simple_Section_Source.h>
#include "State.h"
#include "Transition.h"

namespace aura {
  namespace composing {
    namespace stating {

      template<typename Sound, typename Event=sequencing::Note>
      class State_Machine : public sectioned::Section_Source<Sound, Event> {
          std::vector<State_Pointer<Sound, Event>> states;
          std::vector<Transition_Pointer<Sound, Event>> transitions;
          State<Sound, Event> *current_state = nullptr;

      public:
          sectioned::Section<Sound, Event> get_section() override {
            if (!current_state)
              throw std::runtime_error("Current state is null.");

            auto previous_state = current_state;
            current_state = &current_state->get_transition()->get_next_state(*current_state);
            return previous_state->get_section_source().get_section();
          }

          State<Sound, Event> *create_simple_state(std::initializer_list<sectioned::Clip<Sound, Event>> initializer) {
            auto state = new State<Sound, Event>(new sectioned::Simple_Section_Source<Sound, Event>(initializer));
            states.push_back(State_Pointer<Sound, Event>(state));
            return state;
          }

          void add_transition(Transition_Pointer<Sound, Event> &transition) {
            transitions.push_back(std::move(transition));
          }

          void add_transition(std::initializer_list<State<Sound, Event> *> states,
                              Transition<Sound, Event> *transition) {
            transitions.push_back(Transition_Pointer<Sound, Event>(transition));
            for (auto state : states) {
              state->set_transition(transition);
            }
          }

          State<Sound, Event> *get_state() const {
            return current_state;
          }

          void set_state(State<Sound, Event> &value) {
            current_state = &value;
          }

          void check() {
            for (auto &state : states) {
              if (!state->get_transition())
                throw std::runtime_error("One or more states are missing a transition.");
            }
          }
      };
    }
  }
}