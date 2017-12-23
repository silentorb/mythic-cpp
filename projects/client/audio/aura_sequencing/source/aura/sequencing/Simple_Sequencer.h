#pragma once


#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

using namespace std;

namespace aura {
  namespace sequencing {

    template<typename Event_Type = Note>
    class Simple_Sequencer : public Sequencer<Event_Type> {
        Sequence<Event_Type> &event_source;

    public:
        Simple_Sequencer(Sequence<Event_Type> &source) :
          event_source(source) {
        }

        float get_beats() const {
          return event_source.get_beats();
        }

        int size() const {
          return event_source.size();
        }

        const Note get_note(int index) {
          return event_source.get_note(index);
       }

        void generate_notes(Event_Consumer<Event_Type> &consumer, const Beats range) override {
//          auto beats = get_beats();
//          auto loop_count = range / beats;
          auto loop_count = range / get_beats();
          for (int j = 0; j < loop_count; ++j) {
            float offset = j * 4;
            for (int i = 0; i < event_source.size(); ++i) {
              auto note = get_note(i);
              note.set_start(note.get_start() + offset);
              consumer.add_event(note);
            }
          }
        }
    };

  }
}