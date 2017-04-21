#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

namespace aura {
  namespace sequencing {

    template<typename Event_Type = Note>
    class Transposing_Sequencer : public Sequencer<Event_Type> {
        Sequence <Event_Type> &event_source;
        Chord_Source &chord_source;

    public:
        Transposing_Sequencer(Sequence <Event_Type> &source, Chord_Source &chord_source) :
          event_source(source), chord_source(chord_source) {
        }

        virtual ~Transposing_Sequencer() {}

        float get_beats() const {
          return event_source.get_beats();
        }

        int size() const {
          return event_source.size();
        }

        const Note get_note(int index, Beats offset) {
          auto note = event_source.get_note(index);
          auto &pitch = transpose(*note.get_pitch(), chord_source.get_chord(note.get_start() + offset));
          return Note(pitch, note.get_start() + offset, note.get_duration());
        }

        void generate_notes(Event_Consumer <Event_Type> &consumer, const Beats range) override {
          auto loop_count = range / get_beats();
          for (int j = 0; j < loop_count; ++j) {
            float offset = j * 4;
            for (int i = 0; i < event_source.size(); ++i) {
              auto note = get_note(i, offset);
              consumer.add_event(note);
            }
          }
        }
    };

    template<typename Event_Type = Note>
    class Transposing_Sequencer_Factory{
        std::unique_ptr<Sequence < Event_Type>> event_source;
        Chord_Source &chord_source;

    public:
        Transposing_Sequencer_Factory(Transposing_Sequencer_Factory const &) = delete;

        Transposing_Sequencer_Factory(Chord_Source &chord_source, Beats beats,
                                      std::initializer_list<const Event_Type> initializer):
          event_source(new Sequence<Event_Type>(initializer, beats)),
        chord_source(chord_source){

        }

        std::unique_ptr<Sequencer < Event_Type>> operator()(){
          return std::unique_ptr<Sequencer<Event_Type>>(
            new Transposing_Sequencer<Event_Type>(*event_source, chord_source)
          );
        }
    };
  }
}