#pragma once

#include "Section.h"

namespace aura {
  namespace composing {
    namespace sectioned {

      template<typename Sound, typename Event=sequencing::Note>
      class Simple_Section_Source : public Section_Source<Sound, Event> {
          sectioned::Section<Sound, Event> section;

      public:
          Simple_Section_Source(std::initializer_list<Clip<Sound, Event>> initializer) :
            section(initializer) {}

          Section<Sound, Event> get_section() override {
            return section;
          }
      };

    }
  }
}
