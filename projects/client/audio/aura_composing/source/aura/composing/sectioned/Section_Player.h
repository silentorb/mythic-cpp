#pragma once

#include <aura/performing/Musical_Performer.h>
#include "Section.h"

namespace aura {
  namespace composing {
    namespace sectioned {

      template<typename Sound, typename Event = sequencing::Note>
      class Section_Player {
          Section_Source<Sound, Event> &section_source;

      public:
          Section_Player(Section_Source<Sound, Event> &section_source,
                         performing::Musical_Performer<Sound, Event> &performer) :
            section_source(section_source) {
            performer.set_update_delegate([this](performing::Musical_Performer<Sound, Event> &performer) {
              update(performer);
            });
          }

          void update(performing::Musical_Performer<Sound, Event> &performer) {
            performer.clear();
            auto section = section_source.get_section();
            for (auto &clip: section) {
              performer.add_performance(clip.get_instrument(), clip.get_sequencer());
            }
          }
      };
    }
  }
}