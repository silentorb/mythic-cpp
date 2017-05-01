#pragma once

#include <aura/composing/sectioned/Section.h>
#include <aura/composing/sectioned/Simple_Section_Source.h>
#include "State.h"
#include "Transition.h"
#include <queue>

namespace aura {
  namespace composing {
    namespace stating {

      template<typename Sound, typename Event=sequencing::Note>
      class State_Machine : public sectioned::Section_Source<Sound, Event> {
          std::vector<State_Pointer<Sound, Event>> states;
          std::vector<Transition_Pointer<Sound, Event>> transitions;
          std::vector<State<Sound, Event> *> buffer;
//          State<Sound, Event> *current_state = nullptr;

          void push_state(State<Sound, Event> *state) {
            buffer.push_back(state);
          }

          void pop_buffer() {
            auto state = get_state();
            buffer.erase(buffer.begin());
            if (buffer.size() == 0) {
              push_state(&state->get_transition()->get_next_state(*state));
            }
          }

      public:
          sectioned::Section<Sound, Event> get_section() override {
            auto state = get_state();
            pop_buffer();
            return state->get_section_source().get_section();
          }

          State<Sound, Event> *create_simple_state(std::initializer_list<sectioned::Clip<Sound, Event>> initializer,
                                                   chordial::Chord_Structure_Source &chord_structure_source) {
            auto state = new State<Sound, Event>(new sectioned::Simple_Section_Source<Sound, Event>(initializer),
                                                 chord_structure_source);
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

          State<Sound, Event> *get_state() {
            if (buffer.size() == 0) {
              grow_state_buffer();
            }
//              throw std::runtime_error("Current state is null.");

            return buffer.front();
          }

          State<Sound, Event> *get_state(int index) {
            while (buffer.size() - 1 < index) {
              if (buffer.size() > 32)
                throw std::runtime_error("Possible infinite growth in future chord lookups.");

              grow_state_buffer();
            }
            return buffer[index];
          }

          void set_state(State<Sound, Event> &value) {
            push_state(&value);
          }

          void check() {
            for (auto &state : states) {
              if (!state->get_transition())
                throw std::runtime_error("One or more states are missing a transition.");
            }
          }

          void grow_state_buffer() {
            auto state = buffer.back();
            push_state(&state->get_transition()->get_next_state(*state));
          }
      };
    }
  }
}