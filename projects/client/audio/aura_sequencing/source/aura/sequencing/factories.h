#pragma once

#include "Transposing_Sequencer.h"
#include "Simple_Sequencer.h"
#include "Arpeggio_Sequencer.h"

namespace aura {
  namespace sequencing {

    template<typename Event_Type = Note>
    class Transposing_Sequencer_Factory {
        std::unique_ptr<Sequence<Event_Type>> event_source;
        Chord_Source &chord_source;

    public:
        Transposing_Sequencer_Factory(Transposing_Sequencer_Factory const &) = delete;

        Transposing_Sequencer_Factory(Chord_Source &chord_source, Beats beats,
                                      std::initializer_list<const Event_Type> initializer) :
          event_source(new Sequence<Event_Type>(initializer, beats)),
          chord_source(chord_source) {

        }

        std::unique_ptr<Sequencer<Event_Type>> operator()() {
          return std::unique_ptr<Sequencer<Event_Type >>(
            new Transposing_Sequencer<Event_Type>(*event_source, chord_source)
          );
        }
    };

    template<typename Event_Type = Note>
    class Arpeggio_Sequencer_Factory {
        Arpeggio event_source;
        Chord_Source &chord_source;
        float beats_per_note;

    public:
        Arpeggio_Sequencer_Factory(Arpeggio_Sequencer_Factory const &) = delete;

        Arpeggio_Sequencer_Factory(Chord_Source &chord_source, float beats_per_note,
                                   std::initializer_list<Pitch> initializer) :
          event_source(initializer),
          chord_source(chord_source),
          beats_per_note(beats_per_note) {

        }

        std::unique_ptr<Sequencer<Event_Type>> operator()() {
          return std::unique_ptr<Sequencer<Event_Type >>(
            new Arpeggio_Sequencer<Event_Type>(event_source, chord_source, beats_per_note)
          );
        }
    };

    template<typename Event_Type = Note>
    class Simple_Sequencer_Factory {
        std::unique_ptr<Sequence<Event_Type>> event_source;

    public:
        Simple_Sequencer_Factory(Simple_Sequencer_Factory const &) = delete;

        Simple_Sequencer_Factory(Beats beats,
                                 std::initializer_list<const Event_Type> initializer) :
          event_source(new Sequence<Event_Type>(initializer, beats)) {

        }

        std::unique_ptr<Sequencer<Event_Type>> operator()() {
          return std::unique_ptr<Sequencer<Event_Type >>(
            new Simple_Sequencer<Event_Type>(*event_source)
          );
        }
    };
  }
}