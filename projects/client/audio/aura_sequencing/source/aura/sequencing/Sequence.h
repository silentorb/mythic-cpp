#pragma once

#include "commoner/dllexport.h"
#include "Note.h"
#include "Sequencer.h"
#include <vector>

using namespace std;

namespace aura {
  namespace sequencing {
    class Performer;

    template<typename Event_Type>
    class Sequence : public Sequencer<Event_Type> {
        vector<Note> events;
        Beats beats = 0;

    public:
        Sequence() {}

        Sequence(initializer_list<const Note> initializer, Beats beats) : beats(beats) {
          add_events(initializer);
        }

        Sequence(Beats offset, Beats note_length, initializer_list<const Note> initializer, Beats beats) : beats(
          beats) {
          add_events(offset, note_length, initializer);
        }

        void add_event(const Event_Type &note) {
          events.push_back(note);
          auto end = note.get_start() + note.get_duration();
          if (end > beats)
            beats = end;
        }

        void add_events(initializer_list<const Event_Type> initializer) {
          for (auto &note: initializer) {
            add_event(note);
          }
        }

        void add_events(Beats offset, Beats note_length, initializer_list<const Event_Type> initializer) {
          for (auto &note: initializer) {
            add_event(Note(*note.get_pitch(), note.get_start() + offset, note_length));
          }
        }

        const vector<Event_Type> &get_events() const {
          return events;
        }

        Beats get_beats() const {
          return beats;
        }

        void set_beats(float value) {
          beats = value;
        }

        int size() const {
          return events.size();
        }

        const Event_Type &get_note(int index) {
          return events[index];
        }

        void generate_notes(Event_Consumer <Event_Type> &consumer) override {
          for (auto &note: events) {
            consumer.add_event(note);
          }
        }
    };
  }
}