#pragma once


#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>
#include "Transposing_Sequencer.h"

using namespace std;

namespace aura {
  namespace sequencing {

    template<typename Event_Type = Note>
    class Arpeggio_Sequencer : public Sequencer<Event_Type> {
        const Arpeggio &arpeggio;
        float beats_per_note;
        float beats;
        Chord_Source &chord_source;

    public:
        Arpeggio_Sequencer(const Arpeggio &arpeggio, Chord_Source &chord_source, float beats_per_note) :
          arpeggio(arpeggio), chord_source(chord_source) {
          set_beats_per_note(beats_per_note);
        }

        virtual ~Arpeggio_Sequencer() {}

        float get_beats() const {
          return beats;
        }

        int size() const {
          return arpeggio.size();
        }

        const Event_Type get_event(int index) {
          auto &pitch = transpose(arpeggio.at(index), chord_source.get_chord());
          return Note(pitch, index * beats_per_note, beats_per_note);
        }

        void set_beats_per_note(float value) {
          beats_per_note = value;
          beats = beats_per_note * arpeggio.size();
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer, const Beats range) override {
          int step = 0;
          auto loop_count = range / get_beats();
          for (int i = 0; i < loop_count; ++i) {
            for (auto &event : arpeggio) {
              auto position = step * beats_per_note;
              auto &pitch = transpose(event, chord_source.get_chord(position));
              consumer.add_event(Note(pitch, position, beats_per_note));
              ++step;
            }
          }
        }
    };


    template<typename Event_Type = Note>
    class Delayed_Arpeggio_Sequencer : public Sequencer<Event_Type> {
        const Arpeggio &arpeggio;
        float beats_per_note;
        float beats;
        Chord_Source &chord_source;
        Beats delay;

    public:
        Delayed_Arpeggio_Sequencer(const Arpeggio &arpeggio, Chord_Source &chord_source, float beats_per_note, Beats delay) :
          arpeggio(arpeggio), chord_source(chord_source), delay(delay) {
          set_beats_per_note(beats_per_note);
        }

        virtual ~Delayed_Arpeggio_Sequencer() {}

        float get_beats() const {
          return beats;
        }

        int size() const {
          return arpeggio.size();
        }

        const Event_Type get_event(int index) {
          auto &pitch = transpose(arpeggio.at(index), chord_source.get_chord());
          return Note(pitch, index * beats_per_note, beats_per_note);
        }

        void set_beats_per_note(float value) {
          beats_per_note = value;
          beats = beats_per_note * arpeggio.size();
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer, const Beats range) override {
          int step = 0;
          auto loop_count = range / get_beats();
          for (int i = 0; i < loop_count; ++i) {
            for (auto &event : arpeggio) {
              auto position = step * beats_per_note;
              ++step;
              if (position < delay)
                continue;

              auto &pitch = transpose(event, chord_source.get_chord(position));
              consumer.add_event(Note(pitch, position, beats_per_note));
            }
          }
        }
    };
  }
}