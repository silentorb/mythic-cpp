#pragma once

#include "Transposing_Sequencer.h"
#include "Simple_Sequencer.h"
#include "Arpeggio_Sequencer.h"

namespace aura {
  namespace sequencing {

    template<typename Event = Note>
    class Transposing_Sequencer_Factory : public Sequencer_Factory<Event> {
        Sequence_Pointer <Event> event_source;
        Chord_Source &chord_source;

    public:
        Transposing_Sequencer_Factory(Transposing_Sequencer_Factory const &) = delete;

        Transposing_Sequencer_Factory(Chord_Source &chord_source, Beats beats,
                                      std::initializer_list<const Event> initializer) :
          event_source(new Sequence<Event>(initializer, beats)),
          chord_source(chord_source) {

        }

        Sequencer_Pointer <Event> operator()() {
          return Sequencer_Pointer<Event>(
            new Transposing_Sequencer<Event>(*event_source, chord_source)
          );
        }
    };

    template<typename Event = Note>
    class Arpeggio_Sequencer_Factory : public Sequencer_Factory<Event> {
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

        Sequencer_Pointer <Event> operator()() {
          return Sequencer_Pointer<Event>(
            new Arpeggio_Sequencer<Event>(event_source, chord_source, beats_per_note)
          );
        }
    };

    template<typename Event = Note>
    class Simple_Sequencer_Factory : public Sequencer_Factory<Event> {
        Sequence_Pointer <Event> event_source;

    public:
        Simple_Sequencer_Factory(Simple_Sequencer_Factory const &) = delete;

        Simple_Sequencer_Factory(Beats beats,
                                 std::initializer_list<const Event> initializer) :
          event_source(new Sequence<Event>(initializer, beats)) {

        }

        Simple_Sequencer_Factory(Beats beats, std::initializer_list<const Event> initializer,
                                 Beats beats2, std::initializer_list<const Event> additional) :
          event_source(new Sequence<Event>(beats, initializer, beats2, additional)) {

        }

        Sequencer_Pointer <Event> operator()() {
          return Sequencer_Pointer<Event>(
            new Simple_Sequencer<Event>(*event_source)
          );
        }
    };
  }
}