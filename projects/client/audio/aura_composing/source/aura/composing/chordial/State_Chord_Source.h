#pragma once

#include <aura/sequencing/Note.h>
#include <aura/composing/stating/State_Machine.h>
#include "Chord_Structure_Source.h"

namespace aura {
  namespace composing {
    namespace chordial {

      template<typename Sound, typename Event=sequencing::Note>
      class State_Chord_Source :  public Chord_Structure_Source{
          stating::State_Machine<Sound, Event> &state_machine;
          int measures_per_section = 4;

      public:
          State_Chord_Source(stating::State_Machine<Sound, Event> &state_machine) :
            state_machine(state_machine) {}

          sequencing::Chord_Structure get_chord_structure(const sequencing::Beats &start) override {
            return state_machine.get_state(start / (measures_per_section * 4))->get_chord_structure_source().get_chord_structure(start);
          }
      };
    }
  }
}
