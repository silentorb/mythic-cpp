#pragma once

#include "Clip.h"
#include <vector>
#include <memory>

namespace aura {
  namespace composing {
    namespace sectioned {

      template<typename Sound, typename Event=sequencing::Note>
      using Section = std::vector<Clip<Sound, Event>>;

      template<typename Sound, typename Event=sequencing::Note>
      class Section_Source {
      public:
          virtual Section<Sound, Event> get_section() = 0;
      };

      template<typename Sound, typename Event=sequencing::Note>
      using Section_Source_Pointer = std::unique_ptr<Section_Source<Sound, Event>>;

    }
  }
}