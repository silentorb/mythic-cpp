#pragma once

#include <aura/composing/sectioned/Section.h>
#include <memory>

namespace aura {
  namespace composing {
    namespace stating {

      template<typename Sound, typename Event>
      class Transition;

      template<typename Sound, typename Event=sequencing::Note>
      class State {
          sectioned::Section_Source_Pointer<Sound, Event> section_source;
          Transition<Sound, Event> *transition = nullptr;

      public:
          State(sectioned::Section_Source<Sound, Event> *section_source) :
            section_source(section_source) {}

          sectioned::Section_Source<Sound, Event> &get_section_source() {
            return *section_source;
          }

          Transition<Sound, Event> *get_transition() const {
            return transition;
          }

          void set_transition(Transition<Sound, Event> *value) {
            transition = value;
          }
      };

      template<typename Sound, typename Event=sequencing::Note>
      using State_Pointer = std::unique_ptr<State<Sound, Event>>;
    }
  }
}